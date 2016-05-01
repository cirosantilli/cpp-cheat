# Source tree

Code style is horrible. Whitespaces everywhere. Game programmers ;-)

- examples
    - <https://github.com/bulletphysics/bullet3/blob/2.83/examples/ExampleBrowser/ExampleEntries.cpp>: tree of examples that appears in the browser
    - <https://github.com/bulletphysics/bullet3/blob/2.83/examples/BasicDemo/BasicExample.cpp>: tree of examples that appears in the browser
    - rendering is done from <https://github.com/bulletphysics/bullet3/blob/2.83/examples/ExampleBrowser/GL_ShapeDrawer.cpp> in immediate mode
        - that is called from <https://github.com/bulletphysics/bullet3/blob/2.83/examples/ExampleBrowser/OpenGLGuiHelper.cpp#L447>
        - colors alternate between 4 options: <https://github.com/bulletphysics/bullet3/blob/2.83/examples/ExampleBrowser/OpenGLGuiHelper.cpp#L117>
