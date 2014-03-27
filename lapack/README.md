TODO BROKEN: how to install LAPACKE on Ubuntu 12.04?

BLAS and LAPACK are:

- linear algebra packages
- de-facto standards
- non-parallel 
- originally written in Fortran
- also have C interfaces available

    It might be a good idea to understand how to interface Fortran with C before the C interfaces.

#Related projects

##BLAS

<http://www.netlib.org/blas/>

BLAS contains low level functions such as:

- vector norm
- vector sum
- vector scalar multiplication
- vector matrix multiplication
- matrix matrix multiplication

The BLAS project provides `cblas.h`, which contains a C interface for BLAS.

##LAPACK

LAPACK contains higher level functions such as:

- solving linear systems
- eigenvalue/eigenvector calculations

It now includes an official C interface called `lapacke`.

This does not ship with the Ubuntu `liblapack-dev` package at the time of writing, but there is a `liblapacke-dev` package available which provides it.

##ScaLAPACK

<http://www.netlib.org/scalapack/>

Continuation of LAPACK.

Considers parallelism.

##ATLAS

<http://math-atlas.sourceforge.net/>

Automatically tuned BLAS LAPACK. Not sure what this means, but sounds good!

Implements full BLAS, but only part of LAPACK.

Has C interface.

#Installation on Ubuntu

##Fortran

    sudo aptitude install liblapack-dev liblapack-doc libblas-doc

##C interface

via atlas:

    sudo aptitude install 

via lapacke (`libblas-dev` already contains `cblas.h`):

    sudo aptitude install liblapacke-dev

#Levels

1: array array. ex: array sum.
2: matrix array. ex: solve linear system.
3: matrix matrix. ex: multiply two matrices.

#Function naming conventions

The functions are named according to the pattern:

    XYYZZZ

Where:

- `X`: data type:

    - S: single precision (C float)
    - D: double precision
    - C: complex
    - Z: double complex

- `YY`: known type the type of input matrices:

    - `GE`: general
    - `TR`: triangular

    The more restrict the matrix type, the more efficient algorithms can be.

- `ZZ`: computation to be done:

    - `SV`: SolVe linear system

#Sources

- function signatures: in source code olny <http://www.netlib.org/lapack/double/>

- naming convention <http://www.cs.rochester.edu/~bh/cs400/using_lapack.html>

- user's guide. algorithm info <http://www.netlib.org/lapack/lug/>

- <http://www.tat.physik.uni-tuebingen.de/~kley/lehre/ftn77/tutorial/blas.html>
