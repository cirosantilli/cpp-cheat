# Standards

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

New features are often based on extension of major implementations such as GNU's or Microsoft's.

## Versions

Not all versions were backwards source compatible.

### C89

ANSI ratified the standard in 89, and ISO in 90 only with formatting changes.

### C90

Synonym for C89, because ISO adopted it in 90.

Formal name: ISO/IEC 9899:1990

### C94

### C95

### Normative Addendum 1

Informal names for C89/C90 plus Normative Addendum (aka Amendment) 1, whose primary addition was support for international character sets.

C99 extends this.

### C99

<http://en.wikipedia.org/wiki/C99>

Highly, but not fully backwards compatible: <http://stackoverflow.com/a/30208133/895245>

Major new features:

-   support for `//` comments

-   `long`, `long`, `bool`, complex numbers

-   `gcc` flag: add `-std=c99`

WG14/N1256 is the best free draft available: <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf> Does not seem to exist in HTML: <http://stackoverflow.com/questions/4883212/html-version-of-c-standard-draft-n1256-pdf>

#### Microsoft C99 support

Microsoft stated that they will not update their compilers to C99 and further.

They use C as an inner language, and think it would be too delicate/costly to change it.

They have decided to maintain only C++ and C# up to date. for developers to interface with Windows.

Therefore you will not get those working on MS compiler anytime soon.

### C11

<http://en.wikipedia.org/wiki/C11_%28C_standard_revision%29>

-   latest standard, but very limited support in most compilers as of 2013.

-   previously known as `c1x`

-   supported on `gcc` 4.6+. Flag: `-std=c1x`. It is not recommended to use this yet as support is low.

-   threads

### Terminology

Some tricky terminology from the standards:

#### object

C99 3: anything with storage that can represent values, e.g. `int`, `struct`, `enum`. Non example: functions.

#### Translation unit

Source file after pre processing (5.1.1.1).

## ANSI extensions

Beside ANSI language and libraries, you should also know about the existence of other standards and implementations which extend it:

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
