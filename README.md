# simple-mandelbrot
Winter break coding project, a simple Mandelbrot set rendering program.

More recently, I have been doing work in the "commandline" branch.

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

[!image](http://i.imgur.com/gBWQZva.jpg)

