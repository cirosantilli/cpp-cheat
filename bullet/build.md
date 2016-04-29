# Build

Tested on Ubuntu 2.83.5 in Ubuntu 15.10.

Just forget that `premake` build, use the much more popular CMake and be done with it! Why both exist: <https://github.com/bulletphysics/bullet3/issues/600>

    git clone https://github.com/bulletphysics/bullet3
    git checkout 2.83.5
    mkdir -p build
    cd build
    cmake .. -DBUILD_SHARED_LIBS=ON
    make
    sudo make install

Run examples:

    cd build/examples
    ./ExampleBrowser/App_ExampleBrowser
    ./HelloWorld/App_HelloWorld

If you don't use:

    -DBUILD_SHARED_LIBS=ON

only the static `.a` files are generated, and you will get link errors if you try to use them with `-lBulletSomething`.

The example browser allows you to:

- view simulations OpenGL
- mouse drag objects around
- move camera with mouse wheel or Ctrl + mouse drag

Make dynamic libraries: <https://github.com/bulletphysics/bullet3/issues/447>

TODO: compile examples without the example browser.
