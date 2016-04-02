# Introduction

Simple DirectMedia Layer.

<https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer>

<https://www.libsdl.org/>

Cross platform library for user input (mouse, keyboard, touch), graphics, sound, haptics. Basically a huge wrapper on top of tons of incompatible APIs.

There is some support for hardware acceleration it seems: <https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html>

Made by Loki software <https://en.wikipedia.org/wiki/Loki_Software>

Widely cross platform: Windows, Mac, Linux, Android, [iOS](http://stackoverflow.com/questions/23063659/porting-sdl-app-to-ios).

Widely popular.

Steam for Linux embeds it, and the main dev is working for them as of 2016.

2014 Steam talk <https://www.youtube.com/watch?v=MeMPCSqQ-34>

## Official examples

Ubuntu 15.10 packages tons of examples under `/usr/share/doc/libsdl2-dev/examples.tar.gz`, which are actually the tests under `test/` of the main tree: <http://hg.libsdl.org/SDL>

Those examples seem to use files from other places of the build tree, in particular:

- `build-scripts/` is needed for `./configure` before `make`
- some examples (`testgl`) still fail because they include headers directly from the tree... Remove those from the `Makefile`

## Build

    hg clone http://hg.libsdl.org/SDL
    mkdir -p build && cd build && cmake .. && cmake --build .

Run examples: you must first install it (or checkout to the same version as that installed by your package manager). Then:

    cd test
    ./configure
    make
