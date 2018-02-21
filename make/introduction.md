# Introduction

Make is specified by POSIX 7 <http://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html> and implemented by GNU with extensions. It is the de facto standard make tool for POSIX systems.

Make allows you to:

-   make command line interfaces of the type:

        make <something> a=b c=d

    *very* easily.

-   only build outputs when inputs have changed

    This may save lots of time when building large projects.

## Pros and cons

The main problems of make are:

- not available on Windows
- its Yet Another Scripting Language to learn, and uses Bash inside of it

## Alternatives

Because of the downsides of make, many other make systems have been devised. None has yet dominated on most applications, but important ones include:

-   CMake

-   Rake.

    Similar to `make`, Ruby implemented with Makefiles written in pure Ruby.

-   Apache Ant.

    Written in Java, mainly used for Java project.

    Makefiles are written in XML, so a bit verbose to write by hand.
