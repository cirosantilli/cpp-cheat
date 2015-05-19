# C++

## Standards

Like C, C++ is standardized by ISO under the id: ISO/IEC 14882.

The latest standard costs 30 dollars as of 2013, but free drafts are also available.

Links to several versions: <http://stackoverflow.com/questions/81656/where-do-i-find-the-current-c-or-c-standard-documents>

Drafts are freely available at: <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/>. N3337 seems to be very close to C++11.

Like any standard C++ has several versions noted by year. There are also minor revisions knows as technical reports.

## C++89

First version.

## C++03

Bug fix release, not many new features.

## TR1

## Technical report 1

2005 draft for extending C++11.

Most of its propositions were accepted for C++11, and before that many compilers implemented its propositions.

## TR2

## Technical report 2

TODO when was it made?

Not in C++11, maybe C++1Y.

It proposes many inclusions from Boost.

## C++11

<https://en.wikipedia.org/wiki/C%2B%2B11>

Previously known as C++0x, but took too long to come out.

Unlike C++03, *lots* of new features: standard passes from 800 to 1300 lines.

In `gcc` used to be enabled via `-std=c++0x` flag, now `-std=c++11`. Still marked experimental, but good support for the basic features.

## C++14

Will come after C++11. Known as C++1Y as many have doubts it will come out in 2014.

## stdlib

### STL vs stlib

The term `STL` is *not* mentioned in the C++ ISO standard.

It seems that it was once a separate library which heavily influenced the C++ ISO standrad when it was created.

<http://stackoverflow.com/questions/5205491/whats-this-stl-vs-c-standard-library-fight-all-about>

Therefore: **never** use that word, unless you are really talking about the non stdlib library which has had most of its functionality implemented on the stdlib.

Write `stdlib` and say "Standard Library" instead.

### stdlib implementations

#### GCC libstdc++

GCC comes with an implementation of libstdc++.

#### Apache C++ Standard Library

Dead.

<https://en.wikipedia.org/wiki/Apache_C%2B%2B_Standard_Library>

## Interesting libraries

C++ has many major interesting non standard libs.

### unit testing

Google unit test framework: <http://code.google.com/p/googletest/>

### linear algebra

#### eigen

<http://eigen.tuxfamily.org/index.php?title=Main_Page>

Linear algebra, differential equations.

#### blitz++

<http://blitz.sourceforge.net/>

Linear algebra.

#### armadillo

<http://arma.sourceforge.net/>

Linear algebra.

### tokamak

Rigid body physical engine.

## Funny

-   <https://groups.google.com/forum/#!msg/comp.lang.c++.moderated/VRhp2vEaheU/IN1YDXhz8TMJ>

    Obscure language features.

-   <http://stackoverflow.com/questions/1642028/what-is-the-name-of-this-operator>

    How can this have so many upvotes?

-   <http://stackoverflow.com/questions/6163683/cycles-in-family-tree-software>

    Funny...
