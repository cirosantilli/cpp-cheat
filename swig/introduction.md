# Introduction

<https://en.wikipedia.org/wiki/SWIG>

<http://www.swig.org/doc.html>

Write C/C++ with some extra magic annotations, and generate bindings for several languages, including Python and Java.

Awesome because it can parse your **existing** headers and generate bindings to a ton of languages. Almost no need to touch your C / C++ code.

Works by generating the need:

-   C/C++ files, which you later have to compile into a shared library

-   Python/Java/etc. glue files which use the built-in native API feature of the language, e.g. Java JNI.

    Your Python program then includes that generated file, which contains the API to the C functions.
