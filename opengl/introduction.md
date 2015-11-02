# Introduction

OpenGL is an interface to use the graphics card for graphics.

It only contains basic primitives, and is often used together with other higher level libraries such as GLUT.

OpenGL is only the interface, but there can be several implementations, open and closed source.

## Mesa

<https://en.wikipedia.org/wiki/Mesa_%28computer_graphics%29>

Most common Linux OpenGL implementation. Open source.

Used by the X server.

Requirement of freeglut.

## GLUT

GLUT is a higher level interface built on top of GL, and adds things like:

-   mouse/keyboard input.

    This requires callback functions to be called from an event loop.

-   higher level geometric objects like spheres, cubes and teapots.

The original GLUT implementation is proprietary, but open source implementations exist such as Freeglut.

It is basically a super simple game engine.

### Freeglut

Open source implementation of GLUT.

Often used together with the mesa implementation of GL.

Installation Ubuntu on 12.04:

    sudo aptitude install freeglut3-dev

## glxinfo

Good way to get information on OpenGL in Linux:

    glxinfo | grep -i opengl

Made for the X Window System, but also shows OpenGL information.
