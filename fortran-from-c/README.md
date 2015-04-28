# Fortran from C

How to call Fortran code from C.

## Differences between C and Fortran

-   Fortran appends `_` to the end of symbol names. See that with `readelf -s f.o`.

    Therefore, your c code must look for `f_` functions.

    There are also `-fno-underscore` and `-fno-second-underscore` options to the Fortran compiler.

-   Fortran is case insensitive, and symbols are all lowercased.

-   Fortran arrays are column-major, c is row-major.

    Fortran memory:

        a(1,1)	a(2,1)	a(1,2)	a(2,2)	a(1,3)	a(2,3)

    C memory:

        a[0][0]	a[0][1]	a[0][2]	a[1][0]	a[1][1]	a[1][2]

-   Fortran strings contain length. TODO: how?

-   Fortran `subroutines` pass by reference by default.

    Therefore, corresponding C code must use pointers on function declaration.

    Fortran functions however work like C functions.

-   You must convert corresponding types correctly to match number of bytes and definition.

    This may be hard, because those values may be compiler/machine dependant.

    Not sure there is a bulletproof way to deal with this.

-   You have to link to the Fortran standard library if you want to call functions such as `write` or `abs`.

    In my Ubuntu system, it is called `libgfortran.so.3.0.0`, so `locate fortran.so` should show you the location.

    You could also find this by asking the dependencies of a regular fortran executable as:

        readelf -d executable.elf

## Bibliography

- <http://owen.sj.ca.us/~rk/howto/FandC/FandC.call.html>
- <http://www.yolinux.com/TUTORIALS/LinuxTutorialMixingFortranAndC.html>
