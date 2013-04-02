blas lapack are de-facto standards for non-parallel 
linear algebra computations, originally written in fortran.

besides the standard fortran interface, there are also
some c interfaces available.

#scalapack

    continuation of lapack.

    considers paralellism.

#installation on ubuntu

##fortran

    sudo aptitude install liblapack-dev liblapack-doc

##c interface

    sudo aptitude install libblas3gf


#function naming conventions

`XYYZZZ`

X: data type:

- S: single precision (c float)
- D: double precision
- C: complex
- Z: double complex

YY: the type of matrices:

- GE: general
- TR: triangular

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
