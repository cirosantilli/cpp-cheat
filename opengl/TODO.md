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

    TODO: world vs view  vs projection transforms?

    - http://stackoverflow.com/questions/5550620/the-purpose-of-model-view-projection-matrix
    - http://gamedev.stackexchange.com/questions/56201/opengl-understanding-the-relationship-between-model-view-and-world-matrix

    Possible answer:

    - World: puts objects into place if we were looking from origin. Applied only to objects that need moving.
    - View: `gluLookAt`, places the camera. Applied to all objects.
    - Projection: `glOrtho` and `glFrustum`, prepare the image to project into a 2D plane

-   Make image spin with mouse drag:
    - http://stackoverflow.com/questions/19884182/moving-a-drawing-around-in-opengl-with-mouse
    - http://stackoverflow.com/questions/16342442/drag-and-drop-of-images-using-opengl-c
    - http://stackoverflow.com/questions/20288861/mouse-drag-object-in-opengl-glut
    - http://stackoverflow.com/questions/5734794/mouse-movement-opengl
    - http://stackoverflow.com/questions/1426415/opengl-moving-camera-with-mouse
    - http://gamedev.stackexchange.com/questions/53333/how-to-implement-a-basic-arcball-camera-in-opengl-with-glm
-   VAO, VBO http://stackoverflow.com/questions/11821336/what-are-vertex-array-objects
    -   Immediate mode vs retained mode:
        - https://en.wikipedia.org/wiki/Retained_mode
        - https://en.wikipedia.org/wiki/Immediate_mode_(computer_graphics)
        - immediate mode is deprecated. So like, glBegin, glEnd and glVertex which we use in every test program are deprecated. Lol.
        - http://gamedev.stackexchange.com/questions/21733/why-does-opengl-3-only-allow-vbos
        - http://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl Hello world requested but not provided, too long, lol. Opportunity!
        - http://gamedev.stackexchange.com/questions/21733/why-does-opengl-3-only-allow-vbos
-   https://en.wikipedia.org/wiki/Stencil_buffer
    - http://www.learnopengl.com/#!Advanced-OpenGL/Stencil-testing
-   shading, glsl
    - what is the basis for GLSL implementations? GCC, clang, others?
    - pipeline https://www.opengl.org/wiki/Rendering_Pipeline_Overview , great diagram
        - rasterization: determines which pixels are covered by a triangle
    - name is wrong nowadays: shaders can do more things than just shading, including positioning vertexes (e.g. for tesselation) and arbitrary computaiton!
    - vertex shader
        - gets run for each vertes
        - comes before the fragment shader
        - first pipeline stage
    - fragment shader
        - TODO more precisly, how many times is this called? Once per pixel (for each triangle it appears in)? Seems so:
            - http://gamedev.stackexchange.com/questions/8977/what-is-a-fragment
            - http://gamedev.stackexchange.com/questions/63992/how-many-times-fragment-shader-is-executed
            - http://stackoverflow.com/questions/4421261/vertex-shader-vs-fragment-shader
            - some of those pixels can then be discarded because they are hidden
        - inputs:
            - interpolated colors of vertices of triangles
            - depth
        - a fragment is a piece(s) of a triangle that was behind another one! Thus the name fragment. View: https://youtu.be/uH1ES8LOrlM?t=276
        - comes after rasterization. TODO what is that?
        - <https://www.youtube.com/watch?v=uH1ES8LOrlM>
    - answer http://stackoverflow.com/questions/4421261/vertex-shader-vs-fragment-shader
        - duplicate http://stackoverflow.com/questions/832545/what-are-vertex-and-pixel-shaders
    - http://nehe.gamedev.net/article/glsl_an_introduction/25007/
    - https://www.opengl.org/wiki/Layout_Qualifier_(GLSL)
    - `in`, `out`: http://gamedev.stackexchange.com/questions/29672/in-out-keywords-in-glsl
    - https://www.opengl.org/wiki/Shader
        - there are many types of shaders besides vertex and fragment
    - get output out of glsl
        - http://stackoverflow.com/questions/2508818/how-to-debug-a-glsl-shader
        - http://stackoverflow.com/questions/14086926/get-results-of-gpu-calculations-back-to-the-cpu-program-in-opengl
        - http://stackoverflow.com/questions/19123239/is-it-possible-to-read-data-from-vertex-shader
-   motion blur:
    -   http://john-chapman-graphics.blogspot.fr/2013/01/what-is-motion-blur-motion-pictures-are.html

    | 1 0  0 0 |   | x |   |  x |               | x / -z |
    | 0 1  0 0 | * | y | = |  y | identified to | y / -z |
    | 0 0  1 0 |   | z |   |  z |               |     -2 |
    | 0 0 -1 0 |   | w |   | -z |               |      0 |
