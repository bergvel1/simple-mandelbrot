#ifndef MANDLEBROT
#define MANDLEBROT

// this is the number of pixels per unit along the coordinate axes
#define PIXELS_PER_AXES_UNIT 750 //253

#define WIDTH   (3 * PIXELS_PER_AXES_UNIT + 1)
#define HEIGHT  (2 * PIXELS_PER_AXES_UNIT + 1)
#define	SIZE	(WIDTH * HEIGHT)
#define	M_ITER	255*2
#define	M_MAG	2.0
#define colorDepth 32*4

int * mandelbrot_binary(double x_coords[WIDTH], double y_coords[HEIGHT]);
int * mandelbrot_escape(double x_coords[WIDTH], double y_coords[HEIGHT]);

#endif
