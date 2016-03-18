# GLUT

Most of our examples will use GLUT as the utility library.

GLUT is a higher level interface built on top of GL, and adds things like:

-   mouse/keyboard input.

    This requires callback functions to be called from an event loop.

-   higher level geometric objects like spheres, cubes and teapots.

The original GLUT implementation is proprietary, but open source implementations exist such as Freeglut.

It is basically a super simple game engine.

GLUT wraps system specific code into an uniform API.

All functions are prefixed with `glut`.

## Freeglut

Open source implementation of GLUT.

<http://freeglut.sourceforge.net/>

<https://en.wikipedia.org/wiki/FreeGLUT>

Often used together with the Mesa implementation of GL.

Installation Ubuntu on 12.04:

    sudo aptitude install freeglut3-dev
