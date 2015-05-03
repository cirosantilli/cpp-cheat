# C

## Motivation

C is amazingly important as it is used to implement:

- Linux kernel
- Windows kernel
- Python and Ruby reference implementations
- OpenGL

And the list goes on and on...

The reason for this is that C:

- is quite low level, so you can do low level things other languages can't
- is low level, so it can be very fast (if you program it correctly)
- is robust and easy to understand.

## Standards

## ANSI C

Language and standard library (libc) are standardized by an organization named ANSI

ANSI is American, and it represents the USA for ISO and IEC.

You must pay to have the latest standards, but C99 seems to be available for free [here](http://www.open-std.org/jtc1/sc22/wg14/www/standards.html) (unlike C90, which has larger library support).

Drafts are also available for free, and are very close to the actual standards.

A list of links to the standards can be found at: <http://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents>. Interestingly, as of 2013, C90 costs 141 dollars, but C11 only 30.

However you can get for free:

-   drafts of the latest standard which are quite close to the actual specifications.

    It is strongly recommended that you download this now and try as much as you can to get familiar with it, as it is *the* official source.

-   older standards

-   compiler documentations

ANSI only specifies language and the library interfaces: what functions, variables etc. are contained in each file, but it does not specify how that should be implemented.

Some features are even left for the implementors to decide such as the behavior.

New features are often based on extension of major implementations such as gnu's or Microsoft's.

## C89

ANSI ratified the standard in 89, and ISO in 90 only with formatting changes.

## C90

Synonym for C89, because ISO adopted it in 90.

Formal name: ISO/IEC 9899:1990

## C94

## C95

## Normative Addendum 1

Informal names for C89/C90 plus Normative Addendum (aka Amendment) 1, whose primary addition was support for international character sets.

C99 extends this.

## C99

<http://en.wikipedia.org/wiki/C99>

-   large support, but not 100% by many compilers

-   support for `//` comments

-   `long`, `long`, `bool`, complex numbers

-   gcc flag: add `-std=c99`

-   Microsoft stated that they will not update their compilers to C99 and further.

    They use C as an inner language, and think it would be too delicate/costly to change it.

    They have decided to maintain only C++ and C# up to date. for developers to interface with Windows.

    Therefore you will not get those working on MS compiler anytime soon.

Every C99 citation here will come from WG14/N1256, the best free draft available:
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf

## C11

<http://en.wikipedia.org/wiki/C11_%28C_standard_revision%29>

-   latest standard, but very limited support in most compilers as of 2013.

-   previously known as `c1x`

-   supported on `gcc` 4.6>. Flag: `-std=c1x`.
    It is not recommended to use this yet as support is low.

-   threads

## ANSI extensions

Beside ANSI language and libraries, you should also know about the existence of other standards which extend it:

-   POSIX C library. Offers many functions for POSIX compliant systems (Linux, mac, not windows)

-   Compiler and libc extensions.

    Every compiler has certain language extensions which may be fundamental for certain project.

    For example: gnu C is used on the Linux kernel One major reason is support for inline assembly, which lacks in ANSI C.

If possible you should avoid relying on those since they are less portable.

## glibc

Name for the GNU implementation of the c standard library, and possibly its extensions.

## K&R

## The C Programming Language

<http://en.wikipedia.org/wiki/The_C_Programming_Language>

First edition 1978.

De facto standard for the C language and style for many years.

You will still hear about it in discussions, or even to describe some ANSI C concepts like K&R function declaration.

# Interesting libraries

## PETCs

<http://www.mcs.anl.gov/petsc/documentation/index.html>

## Concurrency

-   C11 supports it, C99 not.

    glibc 2.x still does not have it.

-   C++11 supports it, C++03 not.

-   OpenMP is is a library supported on C, C++, Fortran, Windows, Linux Mac OS.

## Funny

<http://www.ioccc.org/>

<http://www.ioccc.org/years.html>. Amazing.

IOCCC entry explained in detail: <http://stackoverflow.com/questions/15393441/obfuscated-c-code-contest-2006-please-explain-sykes2-c>

## Bibliography

### Free

-   <http://c-faq.com/index.html>

    Good straight to the point faq, covers specially confusing points

-   <http://www.open-std.org/jtc1/sc22/wg14/www/standards>

    Official directory containing the latest free draft versions of the ANSI c specs

    The latest is: <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf>

    The closest to the ANSI standard that you can get for free (it is a paid standard...)

    This should be quite close to the actual specifications

    Quite readable, and fun to find obscure features which you had never heard of before!

-   <http://locklessinc.com/articles/obscurec/>

    Obscure stuff only. Cool.
