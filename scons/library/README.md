# Library

Create and use shared and static libraries.

    scons
    ./main_static.out
    ./main_shared.out
    mv liba.so liba.so.bak
    ./main_static.out
    ./main_shared.out
    # ./main_shared.out: error while loading shared libraries: liba.so: cannot open shared object file: No such file or directory
