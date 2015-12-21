#include "mandelbrot.h"
#include <iostream> // debugging

// Binary computation: only tells whether a point is in the set or not (no divergence times calculated)
int *
mandelbrot_binary(float x[SIZE], float y[SIZE]) {
  std::cout << "Rendering binary image... ";
	static int ret[SIZE];
	float x1, y1, x2, y2;

	for (int i = 0 ; i < SIZE ; i ++) {
		x1 = y1 = 0.0;

		// Run M_ITER iterations
		for (int j = 0 ; j < M_ITER ; j ++) {
			// Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
			x2 = (x1 * x1) - (y1 * y1) + x[i];

			// Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)
			y2 = 2 * (x1 * y1) + y[i];

			// Use the new complex number as input for the next iteration
			x1 = x2;
			y1 = y2;
		}

		// caculate the magnitude of the result
		// We could take the square root, but instead we just
		// compare squares
		ret[i] = ((x2 * x2) + (y2 * y2)) < (M_MAG * M_MAG);
	}

	std::cout << "Done" << std::endl;
	return ret;
}

// Calculates how long it takes each point not in the set to diverge
// currently only scalar
int *
mandelbrot_escape(float x[SIZE], float y[SIZE]) {
  std::cout << "Rendering divergence iteration count image... ";
	static int ret[SIZE];
	float x1, y1, x2, y2;
	int magSq = M_MAG * M_MAG;

	for (int i = 0 ; i < SIZE ; i ++) {
		x1 = y1 = 0.0;

		// number of iterations before divergence
		int iterBeforeEscape = 0;

		// Run M_ITER iterations
		for (int j = 0 ; j < M_ITER ; j ++) {
			// Calculate the real part of (x1 + y1 * i)^2 + (x + y * i)
			x2 = (x1 * x1) - (y1 * y1) + x[i];

			// Calculate the imaginary part of (x1 + y1 * i)^2 + (x + y * i)
			y2 = 2 * (x1 * y1) + y[i];

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

		ret[i] = iterBeforeEscape;
	}

	std::cout << "Done" << std::endl;
	return ret;
}
