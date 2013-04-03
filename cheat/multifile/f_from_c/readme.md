this dir demonstrates calling fotran code from c

#differences between c and fortran

- fortran appends `_` to the end of symbol names. See that with `readelf -s f.o`.

    Threfore, your c code must look for `f_` functions.

    there are also `-fno-underscore` and `-fno-second-underscore` options to the fortran compiler.

- fortran is case insensitive, and symbols are all lowercased.

- fortran arrays are column-major, c is column-minor.

    fortran memory:

        a(1,1)	a(2,1)	a(1,2)	a(2,2)	a(1,3)	a(2,3)

    c memory:

        a[0][0]	a[0][1]	a[0][2]	a[1][0]	a[1][1]	a[1][2]

- fortran strings contain length. TODO:

- fortran `subroutines` pass by reference by default.

    therefore, corresponding c code must use pointers on function declaration.

    fortran functions however work like c functions.

- you must convert correspoinding types correctly to match number of bytes and definition.

    this may be hard, because those values may be compiler/machine dependant.

    not sure there is a bulletproff way to deal with this.

- you have to link to the fotran standard library if you want to call functions such as `write` or `abs`.

    In my Ubuntu system, it is called `libgfortran.so.3.0.0`, so `locate fortran.so` should show you the location.

    You could also find this by asking the dependencies of a regular fortran executable as:
    
        readelf -d executable.elf

#sources

<http://owen.sj.ca.us/~rk/howto/FandC/FandC.call.html>

<http://www.yolinux.com/TUTORIALS/LinuxTutorialMixingFortranAndC.html>
