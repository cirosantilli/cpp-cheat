# Source tree

## Online browsing

## manual

## Documentation

Located under `manual/`.

## sysdeps

Contains both assembly and OS dependant versions of several functions, which makes it one of the most interesting directories.

It contains two kinds of specializations:

-   performance, e.g. `sysdeps/x86_64/multiarch/memcmp-sse4.S` which does `memcmp` really well for SSE-4

-   system call related, which is dependent on the OS used. Linuxers will come again and again to: `sysdeps/unix/sysv/linux`

    TODO: `sysdeps/posix` contains many files which are also present in `sysdeps/unix/sysv/linux`. Why is that? Linux seems to prefer those under `sysdeps/unix/sysv/linux`, which on the build go to the top-level, e.g. `time/clock.o`.

-   `sysdeps/x86_64/dl-machine.h`: true entry point, even before `_start`

Each method also has a pure C implementation when possible, e.g. `string/memcmp.c`, but that is likely to be much less efficient.

### Stub implementations

Basically every directory outside of `sysdeps` contains only stub implementations of anything that is OS related.

E.g., in `posix/getpid.c`:

    int
    __getpid (void)
    {
      __set_errno (ENOSYS);
      return -1;
    }

which simply sets `errno` and returns a failure. Then if for a given system there was no implementation, we get `ENOSYS` as required by POSIX.

### sysdep.h

Important header file that gets included into most files of the architecture, most of which are assembly code.

Example:

- `sysdeps/x86_64/sysdep.h`

It seems that the C preprocessor is used on the assembly code, which does simply `#include <sysdep.h>`.

### multiarch

TODO? as in `sysdeps/x86_64/multiarch`

## elf

## mach

Are those the object formats? Why are they needed on an stdlib? Why no PE as well?

## csu

TODO? What does it mean? Contains the entry points.

## argp

Argument parsing.

Extends POSIX getopt: <http://stackoverflow.com/questions/7677562/whats-the-difference-between-argp-and-getopt>

## io

## libio

## stdio-common

TODO what is the difference?

Low level IO?

Some things which are in each:

- `io`: `read`
- `libio`: `puts`
- `stdio-common`: `printf`

## abilist

TODO

## make-syscalls.sh

## syscall-template.S

## syscalls.list

Generated code for direct system call APIs.
