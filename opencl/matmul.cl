__kernel void kmain(
    __global float *A,
    __global float *B,
    __global float *C,
    const uint n
) {
    uint i, j, k;
    float tmp;

    i = get_global_id(0);
    j = get_global_id(1);
    tmp = 0.0;
    for (k = 0; k < n; ++k)
        tmp += A[i*n+k] * B[k*n+j];
    C[i*n+j] = tmp;
}
