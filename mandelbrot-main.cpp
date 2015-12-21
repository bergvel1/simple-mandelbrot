#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "mandelbrot.h"
#include <cmath>

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

			if(color == 255){
			  p = { color, color, color };
			}

			else{
			  p = rainbow[color%colorDepth];
			}
			
			*image(x, y) = p;
		}
	}

	image.write_to_file(name);
}

int main(int argc, char **argv) {
	static float x_coords[SIZE];
	static float y_coords[SIZE];

	// y axis goes from 1 to -1
	// x axis goes from -2 to 1
	for (int y = 0; y < HEIGHT; ++y) {
		float y_coord = 1.0 - (y * 2.0 / (HEIGHT - 1));
		for (int x = 0; x < WIDTH; ++x) {
			float x_coord = -2.0 + (x * 3.0 / (WIDTH - 1));
			x_coords[y * WIDTH + x] = x_coord;
			y_coords[y * WIDTH + x] = y_coord;
		}
	}

	int *binary_ret = mandelbrot_binary(x_coords, y_coords);
	int *escape_ret = mandelbrot_escape(x_coords, y_coords);

	create_image_binary(binary_ret, "mandelbrot-binary.bmp");
	create_image_bw(escape_ret, "mandelbrot-escape-bw.bmp");
	create_image_color(escape_ret, "mandelbrot-escape-color.bmp");

	return 0;
}
