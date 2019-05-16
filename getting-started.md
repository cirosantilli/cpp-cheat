# Getting started

Tested in Ubuntu 18.10. For other distros, just port `configure`, should be easy.

Build and run all automatable tests:

    ./configure
    ./test

Build and run tests only for one directory non-recursively:

    cd c
    make test

Each test is a normal executable with asserts, so you can run it just with:

    cd c
    ./hello_world.out

Some directories have a `configure` for themselves which needs to be run, e.g.:

    cd boost
    ./configure
    make test

I've been revamping a bunch of the old files when I touch the subject again, but I don't plan to do a full all-out review soon, as I can't make money from this repo :-)

## Interactive directories

If a directory is named just `interactive/`, it does not get run by `test` because it does things like:

- waiting a perceptible amount of time
- waiting for user input
- exiting with status different than 1
