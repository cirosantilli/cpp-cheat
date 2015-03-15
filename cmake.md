# CMake

Make alternative that aims to be:

-   more cross platform: works on Linux and Windows

-   more declarative and compilation focused:
    you declare high level properties, Make translates them to the system.

Generates programs that make the project, including projects for IDEs.

For example, it can generated:

- POSIX `Makefiles` on Linux,
- `cmd.exe` build scripts for Windows
- Code::Blocks project

all from the same input file.

The configuration file is `CMakeLists.txt`, and are written in Yet Another Language.

The standard CMake build process is:

    mkdir build
    cd build
    cmake ..
    cmake --build .

All generated output will be put inside `build`, which should be gitignored.

Yes, you want to define:

    alias cmk='mkdir -p build && cd build && cmake .. && cmake --build .'

CMake also comes with a test driver, `ctest`, which you can use as:

    cd build
    ctest .
