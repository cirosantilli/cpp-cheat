# Toplevel reuse

Use case: you want to reuse:

- a makefile
- several build files (e.g. includes)

for multiple directories.

Concrete example: <https://github.com/cirosantilli/jamesmolloy-kernel-development-tutorials/tree/1d358ed406e6ebe49d2ee8657798aa72652c6bab>

## Rationale

The `proxy.makefile` simply forwards to the main Makefile at the toplevel directory.

We do this instead of directly linking to the toplevel Makefile, as it makes it easier to reuse the shared files on the toplevel like boot.asm without making a new symlink per toplevel file.

Another alternative to this would be to make a directory with shared files, and symlink that directory in. But still that requires one extra symlink per directory, so this method is better.
