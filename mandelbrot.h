#ifndef MANDLEBROT
#define MANDLEBROT

// this is the number of pixels per unit along the coordinate axes
#define PIXELS_PER_AXES_UNIT 750 //253

#define WIDTH   (3 * PIXELS_PER_AXES_UNIT + 1)
#define HEIGHT  (2 * PIXELS_PER_AXES_UNIT + 1)
#define	SIZE	(WIDTH * HEIGHT)
#define	M_ITER	255
#define	M_MAG	2.0
#define colorDepth 32

#include <QImage>

int * mandelbrot_binary(float x[SIZE], float y[SIZE]);
int * mandelbrot_escape(float x[SIZE], float y[SIZE]);
QImage renderMandelbrot(int renderType);

#endif
