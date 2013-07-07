Automatic dependencies installation may be available for your system in a make target of type:
`make install-deps-XXX`, for example, `make install-deps-ubuntu`.

#intro

- linear algebra packages
- de-facto standards
- non-parallel 
- originally written in fortran
- there are also c interfaces available

it might be a good idea to understand how to interface fortran with c
before trying the c interfaces

#install



#related projects

##blas

<http://www.netlib.org/blas/>

blas contains low level functions such as:

- vector norm
- vector sum
- vector scalar multiplication
- vector matrix multiplication
- matrix matrix multiplication

the blas project provides `cblas.h`, which contains a c interface for blas.

##lapack

lapack contains higher level functions such as:

- solving linear systems
- eigenvalue/eigenvector caltulations

it now includes an official c interface called `lapacke`.

this does not ship with the ubuntu `liblapack-dev` package at the time of writting,
but there is a `liblapacke-dev` package available which provides it.

##scalapack

<http://www.netlib.org/scalapack/>

continuation of lapack.

considers paralellism.

##atlas

<http://math-atlas.sourceforge.net/>

automatically tuned blas lapack. not sure what this means, but sounds good!

implements full blas, but only part of lapack.

has c interface.

#installation on ubuntu

##fortran

    sudo aptitude install liblapack-dev liblapack-doc libblas-doc

##c interface

via atlas:

    sudo aptitude install 

via lapacke (`libblas-dev` already contains `cblas.h`):

    sudo aptitude install liblapacke-dev

#levels

1: array array. ex: array sum.
2: matrix array. ex: solve linear system.
3: matrix matrix. ex: multiply two matrices.

#function naming conventions

`XYYZZZ`

X: data type:

- S: single precision (c float)
- D: double precision
- C: complex
- Z: double complex

##YY

known type the type of input matrices

examples:

- GE: general
- TR: triangular

the more restrict the matrix type, the more efficient algorithms will be.

ZZZ: computation to be done:

- SV: SolVe linear system

#sources

- function signatures: in source code olny
    <http://www.netlib.org/lapack/double/>
    
- naming convention
    <http://www.cs.rochester.edu/~bh/cs400/using_lapack.html>

- user's guide. algorithm info
    <http://www.netlib.org/lapack/lug/>

- http://www.tat.physik.uni-tuebingen.de/~kley/lehre/ftn77/tutorial/blas.html
