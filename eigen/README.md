# Eigen

https://eigen.tuxfamily.org/

Tested on Eigen 3.3.4.

## SVD

Calculate the SVD decomposition: https://en.wikipedia.org/wiki/Singular-value_decomposition

    ./svd.out

Output:

    E
    9.52552
    0.5143

    U
    0.229848 -0.883461  0.408249
    0.524745 -0.240783 -0.816496
    0.819642  0.401896  0.408248

    UU'
            1 -5.96046e-08  5.96046e-08
    -5.96046e-08            1  5.96046e-08
    5.96046e-08  5.96046e-08            1

    V
    0.61963 0.784894
    0.784894 -0.61963

    VV'
    1 0
    0 1

    least squares
    -1.33333
    1.08333

This shows how `U` and `V` are unitary.
