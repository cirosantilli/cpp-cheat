#!/usr/bin/env python

import distutils.core

example_module = distutils.core.Extension(
    # Generates a _example.so file.
    # TODO: can this be changed? I'd like to use an `example_python` file to be more explicit.
    '_example',
    sources=['example_wrap_py.c', 'example.c'],
)
distutils.core.setup(
    name = 'example',
    version = '0.1',
    author = "SWIG Docs",
    description = """Simple swig example from docs""",
    ext_modules = [example_module],
    py_modules = ["example"],
)
