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
        - TODO more precisely, how many times is this called? Once per pixel (for each triangle it appears in)? Seems so:
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
    - https://www.shadertoy.com/ the jsfiddle of shaders
    - HLSL: DirectX version of GLSL
-   motion blur:
    -   http://john-chapman-graphics.blogspot.fr/2013/01/what-is-motion-blur-motion-pictures-are.html
-   HUD, billboards, draw pixel on screen:
    - people suggest: glOrtho + disable depth tests
    - could think about a transparent texture right on top of the camera
    - http://stackoverflow.com/questions/4282036/rendering-2d-sprites-in-a-3d-world/36568461#36568461
    - http://stackoverflow.com/questions/6151135/in-opengl-can-i-draw-a-pixel-that-exactly-at-the-coordinates-5-5
    - http://gamedev.stackexchange.com/questions/5959/rendering-2d-sprites-into-a-3d-world/119739#119739
    - glDrawPixels
    - http://stackoverflow.com/questions/6151135/in-opengl-can-i-draw-a-pixel-that-exactly-at-the-coordinates-5-5
    - http://stackoverflow.com/questions/18362058/opengl-draw-pixels-directly
    - http://stackoverflow.com/questions/6644248/how-to-draw-opencl-calculated-pixels-to-the-screen-with-opengl
    - also useful to render "particles": things that are so far / so small that a billboards approximate well enough with less overhead
-   2D acceleration (translation, rotation, alpha blending, z-order) and pixel perfectness:
    - http://stackoverflow.com/questions/10040961/opengl-pixel-perfect-2d-drawing
    - http://stackoverflow.com/questions/3919307/is-there-a-2d-graphics-api-with-both-pixel-perfect-drawing-and-2d-hardware-accel
    - <http://stackoverflow.com/questions/7922526/opengl-deterministic-rendering-between-gpu-vendor>
    - <http://stackoverflow.com/questions/671395/a-simple-2d-cross-platform-graphics-library-for-c-or-c/718384#718384>
-   text, fonts
    - glut does it
    - non trivial: most fonts are specified in vector formats with Bezier curves, and OpenGL does not have any primitives for that
    - the best option is to convert fonts to large textures, and then use those textures
    - http://stackoverflow.com/questions/8847899/opengl-how-to-draw-text-using-only-opengl-methods/36065835#36065835
    - http://stackoverflow.com/questions/14318/using-glut-bitmap-fonts/14319#14319
    - http://stackoverflow.com/questions/2183270/what-is-the-easiest-way-to-print-text-to-screen-in-opengl
    - http://stackoverflow.com/questions/18847109/displaying-fixed-location-2d-text-in-a-3d-opengl-world-using-glut
    - http://stackoverflow.com/questions/9430852/glutbitmapcharacter-positions-text-wrong
    - not in GLFW https://www.reddit.com/r/opengl/comments/2ygsgv/text_on_screen_with_glfw/
-   UV mapping https://en.wikipedia.org/wiki/UV_mapping
    - http://stackoverflow.com/questions/322111/any-one-know-of-an-opengl-es-example-of-an-interactive-globe-earth-for-the-iphon
    - http://stackoverflow.com/questions/17488259/opengl-mapping-texture-to-sphere
    - http://stackoverflow.com/questions/9511499/seam-issue-when-mapping-a-texture-to-a-sphere-in-opengl
-   3D file formats
    - .obj https://en.wikipedia.org/wiki/Wavefront_.obj_file
        - Blender can open it http://stackoverflow.com/questions/4570788/how-can-i-open-obj-files-in-blender
        - created by a 1984 company that was sold to SI https://en.wikipedia.org/wiki/Wavefront_Technologies 
    - .stl https://en.wikipedia.org/wiki/STL_(file_format)
    - BSP https://en.wikipedia.org/wiki/BSP_%28file_format%29 used by Guake, Irrlicht can load them
    - MD2 https://en.wikipedia.org/wiki/MD2_%28file_format%29 animated models, used by Guake 2, Irrlicht can load them
    - viewers / editors:
        - `g3dviewer`: lightweight
-   anti-aliasing, multi-sampling
    - http://www.learnopengl.com/#!Advanced-OpenGL/Anti-aliasing
    - https://en.wikipedia.org/wiki/Subpixel_rendering
-   curve primitives: arcs, Bezier, NURBS: nope?
-   level of detail https://en.wikipedia.org/wiki/Level_of_detail
    - example on bullet physics example browser for spheres: <https://github.com/bulletphysics/bullet3/blob/85368973a1a8b5d0d230feb512fd19540611f923/examples/OpenGLWindow/SimpleOpenGL3App.cpp#L503>
-   detect and highlight which triangle a straight line hits, e.g. for FPS
    - ray casting seems to be the name of this: https://unity3d.com/learn/tutorials/modules/beginner/physics/raycasting
    - bullet can do it: http://bulletphysics.org/mediawiki-1.5.8/index.php/Using_RayTest
    - Irrlicht can do it, 1.8.1 example `./07.collision`
    - https://en.wikipedia.org/wiki/Ray_casting
    - http://stackoverflow.com/questions/14953178/how-to-detect-mouse-over-some-object-in-opengl
    - http://stackoverflow.com/questions/4040616/opengl-gl-select-or-manual-collision-detection
-   dynamic shadows.
    - Irrlicht 1.8.1 example `./08.SpecialFX` does is

## Objects

## Bind

OpenGL is confusing because of those!

<http://stackoverflow.com/a/9760790/895245>

<https://www.quora.com/What-are-buffer-objects-in-OpenGL>

### Container objects

Some objects just contain other objects: <https://www.opengl.org/wiki/OpenGL_Object#Object_types>

E.g. Vertex Array Object is a container <https://www.opengl.org/wiki/Vertex_Specification#Vertex_Array_Object>

### glDrawElements vs glDrawArrays

TODO.

<http://stackoverflow.com/questions/6682771/gldrawelements-vs-gldrawarray-efficiency>

If the last argument of glDrawElements is null, it takes the currently bound:

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
