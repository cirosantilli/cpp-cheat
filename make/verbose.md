# Verbose

How to print the commands that are being run and other things in order to debug large makefiles.

<http://stackoverflow.com/questions/5820303/how-do-i-force-make-gcc-to-show-me-the-commands>

    make -n -f verbose.mk
    make -f verbose.mk SHELL='sh -x'
    make -f verbose.mk -p SHELL='sh -x'
