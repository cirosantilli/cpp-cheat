# Makefile

Build:

    mkdir glibc
    cd glibc
    git clone git://sourceware.org/git/glibc.git src
    cd src
    git checkout glibc-2.21
    cd ..
    mkdir build
    cd build
    # TODO better way? Why is this needed?
    unset LD_LIBRARY_PATH
    GLIBC_INSTALL_DIR="$(pwd)/../install"
    ../src/configure --prefix="$GLIBC_INSTALL_DIR"
    time make -j5
    time make install

Took 4 minutes on a 2012 machine for version 2.21.

Hack and try it out:

    cd ../src

    cat <<'EOS' | git apply -
    diff --git a/libio/ioputs.c b/libio/ioputs.c
    index 39b4bb7..575bb30 100644
    --- a/libio/ioputs.c
    +++ b/libio/ioputs.c
    @@ -51,0 +52,2 @@ weak_alias (_IO_puts, puts)
    +  _IO_sputn (_IO_stdout, "hacked\n", 7);
    +
    diff --git a/stdlib/stdlib.h b/stdlib/stdlib.h
    index 0134378..5d64442 100644
    --- a/stdlib/stdlib.h
    +++ b/stdlib/stdlib.h
    @@ -134,0 +135,2 @@ __END_NAMESPACE_C99
    +#undef EXIT_SUCCESS
    +#define EXIT_SUCCESS 101
    EOS

    make -j5
    make install

    cd /tmp
    echo '
    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        puts("hello world");
        return EXIT_SUCCESS;
    }
    ' > main.c

    # TODO confirm.
    gcc -v -nostdinc -I"$GLIBC_INSTALL_DIR/include" \
      -I'/usr/lib/gcc/x86_64-linux-gnu/4.8/include' \
      -nostartfiles \
      -nodefaultlibs -L"$GLIBC_INSTALL_DIR/lib" \
      -Wl,-rpath="$GLIBC_INSTALL_DIR/lib" \
      "$GLIBC_INSTALL_DIR/lib/crt1.o" \
      "$GLIBC_INSTALL_DIR/lib/crti.o" \
      "$GLIBC_INSTALL_DIR/lib/crtn.o" \
      "$(gcc --print-file-name=crtbegin.o)" \
      "$(gcc --print-file-name=crtend.o)" \
      main.c \
      -lgcc -lc -lgcc -lc

    ./a.out
    echo $?

Output:

    hello world
    hacked
    101

## Using the built stdlib

Not easy.

- <http://stackoverflow.com/questions/2728552/how-to-link-to-a-different-libc-file>
- <http://stackoverflow.com/questions/10763394/how-to-build-a-c-program-using-a-custom-version-of-glibc-and-static-linking>

The best thing to do is likely run `gcc -v` and extract the mandatory commands, while adapting paths to your compiled library.

Things to consider:

-   first disable defaults, then include things, e.g.:

    - `-nostartfiles` followed by the `crt` files
    - `-nostdinc` followed by `-I`
    - `-nostdinc` followed by `-I`

-   `-I'/usr/lib/gcc/x86_64-linux-gnu/4.8/include'` is required by GCC provided headers. I could not get that path programmatically from GCC as I managed for `crtbegin.o` with `--print-file-name`.

-   `-nodefaultlibs -L"$GLIBC_INSTALL_DIR/lib"` for the

-   `-Wl,-rpath="$GLIBC_INSTALL_DIR/lib"` so that `ldd` will be able to find your custom directory when loading

-   `-lgcc -lc -lgcc -lc` twice to resolve interdependencies

Another strategy is to call the smaller programs `cpp`, `gcc -c`, `ld` individually with the paths.

## LD_LIBRARY_PATH during compilation

Make sure that `LD_LIBRARY_PATH` does not contain the current directory, or else when you `cd` into the build directory, things your executables are going to break.

In particular, trailing and leading colons `:` like `:/some/path` imply the current directory!

## Interesting installed files

- `/bin/ldd`
