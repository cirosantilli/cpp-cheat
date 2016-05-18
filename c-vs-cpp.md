# C vs C++

C and C++ are two completely different standards.

C++ attempts to be as much as possible extension of C.

As such, when new C versions such as C99 come out, it is impossible that C++ will immediately follow, but it is very likely that the new C features will be incorporated into C++ if possible in the following versions.

Major differences include:

- classes. Adds enormous complexity and capabilities to the language.
- templates
- stdlib containers
- function overloading
- namespaces

All of those features allow to:

- drastically reduce code duplication
- improve code structure

at the cost of:

-   adding huge complexity to the language.

    The C++ standards have twice as many pages as the C standards.

-   harder to track what assembly code is generated thus:

    -   harder to write very efficient code

    -   generated executables are very large and compilation is slow

        For exmple, at one point I had a 7k line C file whose assembly was 8k lines, but a 7k C++ file generated 55k assembly code lines!

    -   harder to interface with other languages because of name mangling.

        `extern C` reduces the pain a bit: http://stackoverflow.com/questions/1041866/in-c-source-what-is-the-effect-of-extern-c/30526795#30526795

All things considered, C++ offers huge productivity boosts over C *once you learn it*...

It should be used on any new project, except if code efficiency is absolutely crucial, and even in those cases it might be worth it to have a C++ project that use C only features for the 20% critical sections.

## C++11 N3337 standard draft Annex C

Not all behaviour changes in C++ from C are new features!

Some are just deprecation of archaic C ugliness.

This section of the C++ standard lists those differences.

Some examples:

- `static struct` definitions deprecated: <http://stackoverflow.com/questions/7259830/why-and-when-to-use-static-structures-in-c-programming>
- char literals `a` are... chars, not int: <http://stackoverflow.com/questions/433895/why-are-c-character-literals-ints-instead-of-chars>
- implicit `void *` casts are OK in C, but not in C++: <http://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc>
