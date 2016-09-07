# Introduction

OpenGL is an interface to use the graphics card for graphics.

It only contains basic primitives, and is often used together with other higher level libraries such as GLUT.

OpenGL is only the interface, but there can be several implementations, open and closed source.

OpenGL is a C API with bindings to every language. So will will use C for the examples to minimize things.

OpenGL is designed to allow you to talk efficiently with hardware. It would be much simpler to render without the efficiency restriction.  OpenGL's API is greatly complicated by this critical efficiency requirement.

## Mesa

<https://en.wikipedia.org/wiki/Mesa_%28computer_graphics%29>

Dominant Linux desktop OpenGL implementation.

Contains a software implementation, but can also forward to hardware acceleration.

Open source.

Not certified by Khronos.

Used by the X server.

Requirement of freeglut.

OpenGL functions are prefixed with `gl`. Those are the lowest level functions of the API.

## glxinfo

Good way to get information on OpenGL in Linux:

    glxinfo | grep -i opengl

Made for the X Window System, but also shows OpenGL information.
