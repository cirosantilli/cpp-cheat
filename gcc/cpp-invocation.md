# cpp invocation

GNU pre-processor: <https://gcc.gnu.org/onlinedocs/gcc-4.9.2/cpp/>

The executable is called `cpp`.

GCC uses it as a backend.

## D

Make preprocessor defines command line.

Defines can be made from command line arguments:

    gcc -DDEBUG -DLINELENGTH=80 -o c c.c

which is the same as adding:

    #define DEBUG
    #define LINELENGTH 80

to the top of file.

## v

Output verbose information about the compilation.

Great troubleshooting tool.

### Find include search path

    echo '' | cpp -v

Look at sections:

- `include "..." search starts here`:
- `include <...> search starts here`:

### I

Append to the include search path:

    gcc -I/new/include/location/ a.c

The above will not get appended to the existing search path.
For example, if `-Irel/` is used and `/usr/include/` is already on the search path, this does *not* mean that the file `/usr/include/rel/a.h`, can be included via `#include <a.h>`.

### CPATH

Colon separated list of paths to append to the include search path to all languages like `-I`.

## View preprocessed file

This is mostly useful for learning purposes only.

Using `cpp` directly:

	cpp c.c

Outputs the preprocessed file to stdout.

Using `gcc` as a frontend:

    gcc -E c.c

## nostdinc

Don't look for standard includes, only those passed by `-I`.
