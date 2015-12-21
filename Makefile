GCC = g++
GCCFLAGS = -Wall -g -msse -mfpmath=sse -O2

ICC = icpc
ICCFLAGS = -Wall -g -O2 -restrict
VECTOR_FLAGS = -vec-report2
NO_VECTOR_FLAGS = -no-vec

all: mandelbrot

mandelbrot-main.o: mandelbrot-main.cpp mandelbrot.h bmp.h
	$(GCC) $(GCCFLAGS) -c mandelbrot-main.cpp

mandelbrot.o: mandelbrot.cpp mandelbrot.h
	$(GCC) $(GCCFLAGS) -c mandelbrot.cpp

bmp.o: bmp.cpp bmp.h
	$(GCC) $(GCCFLAGS) -c bmp.cpp

mandelbrot: mandelbrot-main.o mandelbrot.o bmp.o
	$(GCC) $(GCCFLAGS) mandelbrot-main.o mandelbrot.o bmp.o -o mandelbrot

clean:
	rm -f mandelbrot *.o *.exe
