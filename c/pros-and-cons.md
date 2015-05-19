# Pros and cons

## Pros

C is amazingly important as it is used to implement:

- Linux kernel
- Windows kernel
- Python and Ruby reference implementations
- OpenGL
- GCC and Binutils (now migrating to C++)

And the list goes on and on...

The reason for this is that C:

- is quite low level, so you can do low level things other languages can't
- is low level, so it can be very fast (if you program it correctly)
- is robust and easy to understand.

## Cons

-   memory leaks

-   obscure features from the 70's for backwards compatibility, many of which trigger compiler warnings even though they are part of the standard:

    - K&R function declarations
    - trigraphs
    - declarations that are not prototypes

    Some were dropped in C99.

