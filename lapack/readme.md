blas lapack are de-facto standards for non-parallel 
linear algebra computations, originally written in fortran.

besides the standard fortran interface, there are also
some c interfaces available.

blas contains low level functions such as:

- vector norm
- vector sum
- vector scalar multiplication
- vector matrix multiplication
- matrix matrix multiplication

lapack contains higher level functions such as:

- solving linear systems
- eigenvalue/eigenvector caltulations

#scalapack

    continuation of lapack.

    considers paralellism.

#installation on ubuntu

##fortran

    sudo aptitude install liblapack-dev liblapack-doc libblas-doc

##c interface

    sudo aptitude install libblas3gf

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
