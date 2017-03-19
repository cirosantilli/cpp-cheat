__kernel void main(
    __global float *A,
    __global float *B,
    __global float *C,
    const uint N
) {
    uint i, j, k;
    float tmp;

    i = get_global_id(0);
    j = get_global_id(1);
    tmp = 0.0;
    for (k = 0; k < N; ++k)
        tmp += A[i*N+k] * B[k*N+j];
    C[i*N+j] = tmp;
}
