# LAPACK

BLAS and LAPACK are:

-   linear algebra packages

-   de-facto standards

-   non-parallel

-   originally written in Fortran

-   also have C interfaces available

    It might be a good idea to understand how to interface Fortran with C before the C interfaces.

Many implementations have been made, so they may be considered interfaces derived from an initial implementation nowadays.

## BLAS

<http://www.netlib.org/blas/>

BLAS contains low level functions such as:

- vector norm
- vector sum
- vector scalar multiplication
- vector matrix multiplication
- matrix matrix multiplication

LAPACK uses BLAS

### BLAS vs LAPACK

LAPACK contains higher level functions such as:

- solving linear systems
- least squares
- eigenvalue/eigenvector calculations

It now includes an official C interface called LAPACKE, which other implementations also implement.

## Implementations

### ScaLAPACK

<http://www.netlib.org/scalapack/>

Continuation of LAPACK.

Considers parallelism distributed across machines.

### ATLAS

<http://math-atlas.sourceforge.net/>

Automatically tuned BLAS LAPACK. Not sure what this means, but sounds good!

Implements full BLAS, but only part of LAPACK.

Has C interface.

### OpenBLAS

<https://github.com/xianyi/OpenBLAS>

### PBLAS

<https://en.wikipedia.org/wiki/PBLAS>

Created and used by ScaLAPACK.

### MKL

Intel's closed source implementation.

## C interface

The BLAS project provides `cblas.h`, which contains a C interface for BLAS (TODO but also an implementation?)

Via atlas:

    sudo aptitude install libatlas-dev
    gcc -lcblas

Via LAPACKE (`libblas-dev` already contains `cblas.h`):

    sudo aptitude install liblapacke-dev
    gcc -lblas

## Levels

1: array array. ex: array sum.
2: matrix array. ex: solve linear system.
3: matrix matrix. ex: multiply two matrices.

## Function naming conventions

<http://www.netlib.org/lapack/lug/node24.html>

The functions are named according to the pattern:

    XYYZZZ

Where:

-   `X`: data type:

    - S: single precision (C float)
    - D: double precision
    - C: complex
    - Z: double complex

-   `YY`: known type the type of input matrices:

    - `GE`: general
    - `TR`: triangular

    The more restrict the matrix type, the more efficient algorithms can be.

-   `ZZ`: computation to be done:

    - `SV`: SolVe linear system
    - `MM`: Matrix Multiply
    - `LS`: Least Squares (overdetermined system)

## Sources

- function signatures: in source code olny <http://www.netlib.org/lapack/double/>

- naming convention <http://www.cs.rochester.edu/~bh/cs400/using_lapack.html>

- user's guide. algorithm info <http://www.netlib.org/lapack/lug/>

- <http://www.tat.physik.uni-tuebingen.de/~kley/lehre/ftn77/tutorial/blas.html>

## LAPACKE

<http://stackoverflow.com/questions/26875415/difference-between-lapacke-and-lapack>
