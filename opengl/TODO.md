# TODO

-   Are the OpenGL types fixed size? How to properly printf them?
-   How to select the rendering device? <http://stackoverflow.com/questions/6036292/select-a-graphic-device-in-windows-opengl> `prime-select`?
-   Do everything without GLUT for Linux to learn what is going on. Windowing and events are likely not worth the trouble...
    -   <http://stackoverflow.com/questions/879035/initializing-opengl-without-glut>
    -   <http://stackoverflow.com/questions/5608767/learning-opengl-without-glut>
    -   <https://www.opengl.org/discussion_boards/showthread.php/177999-GCC-OpenGL-without-glut>
-   Understand the matrix stack, `glLoadMatrixg`. Major application: define new points relative to the previous view. E.g.: wheels of a car relative to the car.
    - <http://gamedev.stackexchange.com/questions/72044/why-do-we-use-4x4-matrices-to-transform-things-in-3d>
    - <http://stackoverflow.com/questions/13647108/matrix-stacks-in-opengl-deprecated>
    - <http://stackoverflow.com/questions/3755998/what-is-the-point-of-the-matrix-stack-in-opengl>
    - <http://gamedev.stackexchange.com/questions/83725/new-to-opengl-having-trouble-understanding-matrix-transformation>
    - <https://www.reddit.com/r/learnprogramming/comments/1sipqz/why_does_opengl_use_4x4_matrices_to_describe_3d/>

    1) Why use matrices at all? Answer: to pre-calculate multiple combined operations.
    2) Why 4D for 3D objects? Let's see 3D for 2D and then we're done.

    TODO: world, view and projection transforms?
-   Make image spin with mouse drag:
    - http://stackoverflow.com/questions/19884182/moving-a-drawing-around-in-opengl-with-mouse
    - http://stackoverflow.com/questions/16342442/drag-and-drop-of-images-using-opengl-c
    - http://stackoverflow.com/questions/20288861/mouse-drag-object-in-opengl-glut
    - http://stackoverflow.com/questions/5734794/mouse-movement-opengl
    - http://stackoverflow.com/questions/1426415/opengl-moving-camera-with-mouse
    - http://gamedev.stackexchange.com/questions/53333/how-to-implement-a-basic-arcball-camera-in-opengl-with-glm
-   VAO, VBO http://stackoverflow.com/questions/11821336/what-are-vertex-array-objects
    -   Immediate mode vs retained mode:
        - immediate mode is deprecated. So like, glBegin, glEnd and glVertex which we use in every test program are deprecated. Lol.
        - http://gamedev.stackexchange.com/questions/21733/why-does-opengl-3-only-allow-vbos
        - http://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl Hello world requested but not provided, too long, lol. Opportunity!
        - http://gamedev.stackexchange.com/questions/21733/why-does-opengl-3-only-allow-vbos
-   https://en.wikipedia.org/wiki/Stencil_buffer
-   shading
    - vertex shader
    - fragment shader
