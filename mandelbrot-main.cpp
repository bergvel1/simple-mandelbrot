#include <stdio.h>
#include <stdlib.h>
#include <QImage>
#include <QString>
#include "mandelbrot.h"

#include <cmath>

typedef unsigned char     uint8_t;  //for some reason this is necessary in windows

QImage
create_image_binary(int *ret, const char *name) {
    QImage renderedImage = QImage(WIDTH, HEIGHT, QImage::Format_Mono);

    //setup color table
    QRgb value;
    value = qRgb(0, 0, 0); //0xff000000
    renderedImage.setColor(0, value);
    value = qRgb(255, 255, 255); //0xffffffff
    renderedImage.setColor(1,value);

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			// white for points out of set, black for points in set
            renderedImage.setPixel(x,y,!(ret[(y*WIDTH) + x]));
		}
	}

    return renderedImage;
}

QImage
create_image_bw(int *ret, const char *name) {
    QImage renderedImage = QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
            // white for points in set, gradient to black for iterations until divergence
            QRgb value;
			uint8_t color = ret[y * WIDTH + x];
            value = qRgb(color, color, color);
            renderedImage.setPixel(x, y, value);
		}
	}

    return renderedImage;
}


QImage
create_image_color(int *ret, const char *name) {
  float frequency = 0.3/(colorDepth/32);
  QRgb rainbow[colorDepth];
  
  for(int i = 0; i < colorDepth; i++){
    //generate 32 rainbow colors with detuned sines
    uint8_t red = sin(frequency*i + 0)*127 + 128;
    uint8_t green = sin(frequency*i + 2)*127 + 128;
    uint8_t blue = sin(frequency*i + 4)*127 + 128;

    QRgb curr = qRgb(red, green, blue);

    rainbow[i] = curr;
  }

  
    QImage renderedImage = QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
            uint8_t escapeIter = ret[y * WIDTH + x];
            QRgb value;

            if(escapeIter == 255){
              value = qRgb(escapeIter, escapeIter, escapeIter);
			}

			else{
              value = rainbow[escapeIter%colorDepth];
			}
			
            renderedImage.setPixel(x, y, value);
		}
	}

    return renderedImage;
}

QImage renderMandelbrot(int renderType) {
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

    if(renderType == 0){
        int *binary_ret = mandelbrot_binary(x_coords, y_coords);
        return create_image_binary(binary_ret, "mandelbrot-binary.bmp");
    }
    else{
        int *escape_ret = mandelbrot_escape(x_coords, y_coords);

        if(renderType == 1)
            return create_image_bw(escape_ret, "mandelbrot-escape-bw.bmp");
        else
            return create_image_color(escape_ret, "mandelbrot-escape-color.bmp");
    }

}
