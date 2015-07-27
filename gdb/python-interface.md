# Python interface

Python API for GDB. Whenever your script starts getting a little more complex, you will need to use it.

## Usage

All scripts are in Python 3.

Each Python file in this directory can be run with:

    gdb --batch -x name.py

Some of those files have corresponding C files that must be compiled before running the script. The naming convention for those C files is `name_py.c`.

## Run a python script

You can run a Python script with either `-x`:

    gdb --batch -x name.py

or from inside GDB:

    source name.py

The script type is recognized from the file extension.

## The interface is not Python only

There seem to be many operations which need `execute` to be done.

What the API does it to parse the GDB information into Python.

To suppress `execute` stdout, you will often use:

    execute('cmd', to_string=True)

## py

## python command

Single command:

    py print(123)

Multiple lines:

    (gdb) py
    >print(123)
    >end

Scripts can be sourced with:

    source script.py

GDB knows that they are Python and not `.gdb` scripts by the file extension.

## python-interactive

## pi

Start a Python shell inside GDB:

    (gdb) pi
    >>> a = 1
    >>> print(a)
    1

Exit with Ctrl + D.

## Bibliography

- `help gdb` from the python shell. Great way to see what the API contains. Then read the `.texi` docs for the details.

- <https://sourceware.org/gdb/wiki/PythonGdbTutorial> 2008 tutorial by the API author. Somewhat outdated.

Libraries that use it:

- <https://github.com/longld/peda/>
- <https://github.com/stephenbradshaw/pygdbdis/blob/master/pygdbdis.py>
- <https://github.com/jfoote/exploitable>
