# Cross compile

TODO get working.

Official docs: <https://gcc.gnu.org/install/build.html> "Building a cross compiler" section.

Official wiki: <https://gcc.gnu.org/wiki/Building_Cross_Toolchains_with_gcc>

3 parameters identify the cross compiler: <http://wiki.osdev.org/Target_Triplet>

TODO: list all possible targets:

- <https://gist.github.com/roxlu/4637059>
- <https://gcc.gnu.org/install/specific.html>
- <http://wiki.osdev.org/GCC_Cross-Compiler>

## Name convention

Some samples:

Ubuntu 16.04:

- `arm-linux-gnueabi-`: Ubuntu 16.04 `binutils-arm-linux-gnueabi`, `binutils-arm-linux-gnueabihf` packages
- `arm-linux-gnueabihf-`: Ubuntu 16.04 `gcc-arm-linux-gnueabihf`
- `arm-linux-androidabi-`: Android NDK 16
- `arm-none-eabi-`: Ubuntu 16.04 `gcc-arm-none-eabi` package. Suitable to compile bare metal code that does not link to libc.
- `x86_64-linux-gnu-`: Ubuntu 16.04 `gcc` package
