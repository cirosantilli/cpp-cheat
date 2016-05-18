# Utility libraries

Utility libraries built on top of OpenGL.

## GLU

<https://en.wikipedia.org/wiki/OpenGL_Utility_Library>

Functions prefixed with `glu`

Mesa implements it apparently, e.g. `dpkg` shows `libglu1-mesa`.

## GLEW

<https://en.wikipedia.org/wiki/OpenGL_Extension_Wrangler_Library>

## GLFW

GLUT alternative. More features, more modern, thus recommended by some people.

<http://stackoverflow.com/questions/25708688/what-is-the-difference-between-freeglut-vs-glfw>

<https://en.wikipedia.org/wiki/GLFW>

One advantage over GLUT seems to be that it allows for more control over the event loop:
<http://gamedev.stackexchange.com/questions/8623/a-good-way-to-build-a-game-loop-in-opengl?lq=1>

## GLM

C++ Mathematics useful for OpenGL.

<https://github.com/g-truc/glm>

C alternatives?

- <https://www.reddit.com/r/gamedev/comments/1uhnlg/good_glm_alternatives_for_c/>

## SOIL

C image to textures.

<http://www.lonesock.net/soil.html>

## OGRE

<https://en.wikipedia.org/wiki/OGRE>

OpenGL wrapper.

Not a full game engine.

Supports multiple backends, including Direct3D as well, possibly giving more portability / performance.

Even if you forget portability, it makes it easier to use OpenGL with some more convenient primitives. E.g.:

- it can draw a sphere: <http://www.ogre3d.org/docs/api/1.9/class_ogre_1_1_sphere.html>

MIT license.

## Closed source

- <https://en.wikipedia.org/wiki/Poser>
