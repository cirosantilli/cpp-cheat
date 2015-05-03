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

-   adding huge complexity to the language (probably at least doubles the complexity).

    The problem is that individual features sometimes interact in ways which are not obvious to understand, so the complexity growth is exponential per feature.

-   making it harder to track what assembly code is generated thus:

    -   making it harder to write very efficient code

    -   generating executables that are very large

        For exmple, at one point I had a 7k line C file whose assembly was 8k lines, but a 7k C++ file generated 55k assembly code lines!!

All things considered, C++ offers huge productivity boosts over C *once you learn it*... It should be used on any new project, except if code efficiency is absolutelly crucial, and even in those cases it might be worth it to have a C++ project that use C only features for the 20% critical sections.
