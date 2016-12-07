# Build

Build from source.

Ubuntu 16.10

    hg clone http://hg.libsdl.org/SDL
    hg checkout release-2.0.4
    mkdir -p build
    cd build
    # TODO: -DVIDEO_WAYLAND=OFF or else link fails with undefined reference to
    # wl_proxy_marshal_constructor_versioned
    cmake -DVIDEO_WAYLAND=OFF ..
    cmake --build .

Run examples: you must first install it (or checkout to the same version as that installed by your package manager). Then:

    cd test
    # TODO: patch with:
    # https://bugzilla.libsdl.org/show_bug.cgi?id=3508
    ./configure
    make
