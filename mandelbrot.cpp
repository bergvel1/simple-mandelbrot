#include "mandelbrot.h"
#include <iostream> // debugging

// Binary computation: only tells whether a point is in the set or not (no divergence times calculated)
int * 
mandelbrot_binary(double x_coords[WIDTH], double y_coords[HEIGHT]){
	std::cout << "Here goes nothing... ";
	static int ret[SIZE];
	double x1, y1, x2, y2;
	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			x1 = y1 = 0.0;

			for (int i= 0 ; i < M_ITER ; i ++) {
				// Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
				x2 = (x1 * x1) - (y1 * y1) + x_coords[x];

				// Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)
				y2 = 2 * (x1 * y1) + y_coords[y];

				// Use the new complex number as input for the next iteration
				x1 = x2;
				y1 = y2;
			}

			// caculate the magnitude of the result
			// We could take the square root, but instead we just
			// compare squares
			ret[(WIDTH*y)+x] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
		}
	}
	std::cout << "Done" << std::endl;
	return ret;
}

// Calculates how long it takes each point not in the set to diverge
int *
mandelbrot_escape(double x_coords[WIDTH], double y_coords[HEIGHT]) {
  std::cout << "Rendering divergence iteration count image... ";
	static int ret[SIZE];
	double x1, y1, x2, y2;
	int magSq = M_MAG * M_MAG;

	for(int x = 0; x < WIDTH; x++){
		for(int y = 0; y < HEIGHT; y++){
			x1 = y1 = 0.0;

			// number of iterations before divergence
			int iterBeforeEscape = 0;

			// Run M_ITER iterations
			for (int i = 0 ; i < M_ITER ; i ++) {
				// Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
				x2 = (x1 * x1) - (y1 * y1) + x_coords[x];

				// Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)
				y2 = 2 * (x1 * y1) + y_coords[y];

				// Use the new complex number as input for the next iteration
				x1 = x2;
				y1 = y2;

				// if we're over the divergence threshold, break
				if(((x2 * x2) + (y2 * y2)) >= magSq){
				  break;
				}

			// increment for each iteration below divergence threshold
			iterBeforeEscape++;
		}

		ret[(WIDTH*y)+x] = iterBeforeEscape;
		}
	}

	std::cout << "Done" << std::endl;
	return ret;
}
