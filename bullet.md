# Bullet

## Build

Tested on Ubuntu 2.83.5 in Ubuntu 15.10.

    git clone https://github.com/bulletphysics/bullet3
    cd build3
    ./premake4_linux gmake
    cd gmake
    make

Outputs are `.a` and executables under `bin/`. The most interesting is:

    ./bin/App_ExampleBrowser_gmake_x64_release

which allows you to view with OpenGL and interact with mouse dragging with the examples under `examples/`.
