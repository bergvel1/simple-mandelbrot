# simple-mandelbrot
Winter break coding project, a simple Mandelbrot set rendering program.

# how to use
This program takes five arguments:
  1. A filename (default render.bmp)
  2. An integer indicating the render type, with three possible options:
    0: a binary b/w render
    1: a b/w escape iteration render (default option)
    2: a color escape iteration render
  3. A float describing the center x coordinate (default -0.5)
  4. A float describing the center y coordinate (default 0.0)
  5. The zoom factor, given as a float (default 1.0)

Alternatively, you may run this program with no arguments, and default options will be used.

# other notes
I recommend testing out different values for M_ITER in mandelbrot.h when doing deep zooms. Depending on how large of a zoom factor you're trying to use, you'll probably want to increase the number of iterations. I think there's a way to calculate the ideal number to use, so I'll probably automate this at some point.

# some pictures
![Alt text](/render.bmp?raw=true "Optional Title")
![Alt text](/render2.bmp?raw=true "Optional Title")
