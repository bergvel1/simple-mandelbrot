A simple Mandelbrot set generator. Currently produces three renderings:
a binary view (each pixel is either in or out of the set), and two views
(one black-white and one color) of the number of iterations a given point
stays under the escape radius of 2.0.

TODO:
Add GUI
Add support for specifying zoomed in areas of complex plane to render
Vectorize escape iteration calculation function
Implement antialiasing? Some edges look very jagged
Continuous coloring support
