#installation on ubuntu 12.04

- blas
    sudo aptitude install libblas3gf

#naming conventions

    XYYZZZ

    X: data type
    S 	single precision (c float)
    D 	double precision
    C 	complex
    Z 	double complex

    YY: the type of matrices
    - GE general
    - TR triangular

    ZZZ: computation

#sources

- function signatures: in source code olny
    <http://www.netlib.org/lapack/double/>
    
- naming convention
    <http://www.cs.rochester.edu/~bh/cs400/using_lapack.html>

- user's guide. algorithm info
    <http://www.netlib.org/lapack/lug/>

- http://www.tat.physik.uni-tuebingen.de/~kley/lehre/ftn77/tutorial/blas.html
