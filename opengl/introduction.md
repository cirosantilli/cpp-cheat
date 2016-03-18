# Introduction

OpenGL is an interface to use the graphics card for graphics.

It only contains basic primitives, and is often used together with other higher level libraries such as GLUT.

OpenGL is only the interface, but there can be several implementations, open and closed source.

OpenGL is a C API with bindings to every language. So will will use C for the examples to minimize things.

## Mesa

<https://en.wikipedia.org/wiki/Mesa_%28computer_graphics%29>

Dominant Linux desktop OpenGL implementation.

Contains a software implementation, but can also forward to hardware acceleration.

Open source.

Not certified by Khronos.

Used by the X server.

Requirement of freeglut.

OpenGL functions are prefixed with `gl`. Those are the lowest level functions of the API.

## Libraries built on top of OpenGL

GLUT.

### GLU

<https://en.wikipedia.org/wiki/OpenGL_Utility_Library>

Functions prefixed with `glu`

Mesa implements it apparently, e.g. `dpkg` shows `libglu1-mesa`.

### GLEW

<https://en.wikipedia.org/wiki/OpenGL_Extension_Wrangler_Library>

### GLFW

GLUT alternative. More features, more modern, thus recommended by some people.

<http://stackoverflow.com/questions/25708688/what-is-the-difference-between-freeglut-vs-glfw>

<https://en.wikipedia.org/wiki/GLFW>

One advantage over GLUT seems to be that it allows for more control over the event loop:
<http://gamedev.stackexchange.com/questions/8623/a-good-way-to-build-a-game-loop-in-opengl?lq=1>

### GLM

Mathematics useful for OpenGL.

<https://github.com/g-truc/glm>

## glxinfo

Good way to get information on OpenGL in Linux:

    glxinfo | grep -i opengl

Made for the X Window System, but also shows OpenGL information.

## Users

- <https://en.wikipedia.org/wiki/OGRE> OpenGL rendering front-end that supports multiple backends, including Direct3D as well. Not a full game engine.
