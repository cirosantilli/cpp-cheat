# Internals

Hardware vs software breakpoints: <http://stackoverflow.com/questions/8878716/what-is-the-difference-between-hardware-and-software-breakpoints> x86 has 4 registers which can raise an exception is the PC points to the instruction stored in them. GDB can then deal with the exception and take over.

## Communication

- bugs and feature requests at: <https://sourceware.org/bugzilla>
- patches: <https://sourceware.org/ml/gdb-patches/>
- wiki: <https://sourceware.org/gdb/wiki/EditorGroup> You need permission to write... so useless for documentation, which should go in the source instead.

## Make

You cannot run `make && make install` just for GDB: you have to rebuild the entire Binutils every time, or might segfault.

## Tests

Under `gdb/testsuite`. Do take a look at the README.

Run all:

    # MANUAL
    #path_to_latest_stable_gcc=''
    #export PATH="$path_to_latest_stable_gcc:$PATH"
    sudo apt-get build-dep gdb
    # TODO: prelink is too old in Ubuntu 14.04.
    sudo apt-get install gccgo gnat guile prelink systemtap-sdt-dev
    # ptrace without sudo
    # Tons of tests fail by default on Ubuntu because you cannot attach:
    # https://sourceware.org/bugzilla/show_bug.cgi?id=18067
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    # `bigcore.exp` is broken on Ubuntu by default because of Apport:
    # https://sourceware.org/bugzilla/show_bug.cgi?id=18704
    echo | sudo tee /proc/sys/kernel/core_pattern
    ulimit -c unlimited
    cd build/gdb/testsuite
    # Running tests in parallel finishes in a third of the time,
    # but also generates way more failures as of 7.9.1...
    make check


Only run a few:

    make check TESTS="gdb.python/*.exp"

All but one:

    make check RUNTESTFLAGS="--ignore gbd.base/bigcore.exp"

### Official CI

Info: <https://sourceware.org/gdb/wiki/BuildBot>

Buildbot: <http://gdb-build.sergiodj.net/>, most useful page for me: <http://gdb-build.sergiodj.net/builders/Debian-x86_64-m64>

The framework is open source: <https://github.com/buildbot/buildbot>

Actual configuration used (I think): <http://git.sergiodj.net/?p=gdb-buildbot.git;a=summary> on the personal Git server of a Red Hat employee...

Not all commits are tested to save CPU.

Buildbot cannot show old logs: <http://trac.buildbot.net/ticket/3320> <http://stackoverflow.com/questions/31581472/how-to-get-the-build-for-a-given-commit-revision-from-the-web-interface-in-bui>

Instead, each projects exports those logs in some way.

GDB uses both:

- daily emails to a mailing list with a single commit per day: <https://sourceware.org/ml/gdb-testers/>
- one Git repository per machine, all of them under a cgit UI: <http://gdb-build.sergiodj.net/cgit>

## Vocabulary

- `sal`: symtable and line. Both are often passed around together. TODO why.

## Source tree

- `gdb.c`: entry point
- `cli/cli-cmds.c`: defines the built-in commands. Good place to start probing. Not *all* commands are there however. Grep for strings, e.g. `"break"`.
- `syscalls`: map of system calls string names to numbers. Likely used by CLI functionality that allows you to enter system call names, e.g. `catch syscall`.

## Functions

- `add_com`: add command. By convention, functions that defined commands are named as `XXX_command`.
