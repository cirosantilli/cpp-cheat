opengl is just an interface to use the graphics card
for graphics. Therefore it only contains basic primitives.

opengl is only the interface, but there can be several implentations

#mesa

most common linux free Opengl implementation

used by X server

requirement of <#freeglut>

#glut

glut is based on gl, and adds things like:

- mouse/keyboard input
- geometric objects like spheres, cubes and teapots

the original glut implementation is proprietary

#freeglut

is an open source implementation of glut

it is often associated with the <#mesa> implementation of gl

already installs mesa opengl on which it depends
              
#installation ubuntu on 12.04

    sudo aptitude update
    sudo aptitude install build-essential
    sudo aptitude install freeglut3-dev
        #installs mesa opengl as dependency
