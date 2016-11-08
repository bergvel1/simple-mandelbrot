#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "mandelbrot.h"
#include <cmath>
#include <iostream> 

void
create_image_binary(int *ret, const char *name) {
	bmp image(WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			// white for points out of set, black for points in set
			uint8_t color = !ret[y * WIDTH + x] * 255;
			pixel p = { color, color, color };
			*image(x, y) = p;
		}
	}

	image.write_to_file(name);
}

void
create_image_bw(int *ret, const char *name) {
	bmp image(WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			// white for points out of set, black for points in set
			uint8_t color = ret[y * WIDTH + x];
			pixel p = { color, color, color };
			*image(x, y) = p;
		}
	}

	image.write_to_file(name);
}

void
create_image_color(int *ret, const char *name) {
  float frequency = 0.3/(colorDepth/32);
  pixel rainbow[colorDepth];
  
  for(int i = 0; i < colorDepth; i++){
    //generate 32 rainbow colors with detuned sines
    uint8_t red = sin(frequency*i + 0)*127 + 128;
    uint8_t green = sin(frequency*i + 2)*127 + 128;
    uint8_t blue = sin(frequency*i + 4)*127 + 128;

    pixel curr = {red, green, blue};

    rainbow[i] = curr;
  }

  
	bmp image(WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			uint8_t color = ret[y * WIDTH + x];
			pixel p;

			if(color == M_ITER){
			  p.blue = 255;
			  p.green = 255;
			  p.red = 255;
			}

			else{
			  p = rainbow[color%colorDepth];
			}
			
			*image(x, y) = p;
		}
	}

	image.write_to_file(name);
}

// ARGUMENTS
// 1. Filename
// 2. Render type
// 3. x center
// 4. y center
// 5. zoom factor
int main(int argc, char **argv) {
    const char * filename;
    int render_type;
    double center_x;
	double center_y; 
	double zoom_factor;
	  
    if (argc == 1){
    	std::cout << "Running with default settings..." << std::endl;
    	filename = "render.bmp";
    	render_type = 1;
    	center_x = -0.5;
    	center_y = 0.0;
    	zoom_factor = 1.0;
    }
    else if (argc == 6){
    	std::cout << "Running with user settings..." << std::endl;
    	filename = argv[1];
    	render_type = atoi(argv[2]);
    	center_x = strtod(argv[3],NULL);
    	center_y = strtod(argv[4],NULL);
    	zoom_factor = strtod(argv[5],NULL);
    }
    else{
    	std::cout << "Welcome to my simple Mandelbrot renderer!" << std::endl;
    	std::cout << "This program takes five arguments:" << std::endl;
    	std::cout << "\t1. A filename (default render.bmp)" << std::endl;
    	std::cout << "\t2. An integer indicating the render type, with three possible options:" << std::endl;
    	std::cout << "\t\t0: a binary b/w render" << std::endl;
    	std::cout << "\t\t1: a b/w escape iteration render (default option)" << std::endl;
    	std::cout << "\t\t2: a color escape iteration render" << std::endl;
    	std::cout << "\t3. A float describing the center x coordinate (default -0.5)" << std::endl;
    	std::cout << "\t4. A float describing the center y coordinate (default 0.0)" << std::endl;
    	std::cout << "\t5. The zoom factor, given as a float (default 1.0)" << std::endl;
    	std::cout << "Alternatively, you may run this program with no arguments, and default options will be used" << std::endl;
    	return 1;
    }

	static double x_coords[WIDTH];
	static double y_coords[HEIGHT];

	double y_low = center_y-(1.0/zoom_factor); //  -1.0
	double y_high = center_y+(1.0/zoom_factor); //  1.0
	double x_low = center_x - (1.5/zoom_factor); // -2.0
	double x_high = center_x + (1.5/zoom_factor); //  1.0

	for (int y = 0; y < HEIGHT; ++y){
		y_coords[y] = y_high - (y * (-1.0*(y_low-y_high)) / (HEIGHT - 1));
	}

	for (int x = 0; x < WIDTH; ++x){
		x_coords[x] = x_low + (x * (x_high-x_low) / (WIDTH - 1));
	}

	if(render_type == 0){
		int *binary_ret = mandelbrot_binary(x_coords, y_coords);
		create_image_binary(binary_ret, filename);
	}
	else{
		int *escape_ret = mandelbrot_escape(x_coords, y_coords);
		if(render_type == 1) create_image_bw(escape_ret, filename);
		else create_image_color(escape_ret, filename);
	}

	return 0;
}
