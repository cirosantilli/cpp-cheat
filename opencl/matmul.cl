__kernel void main(
    __global float *A,
    __global float *B,
    __global float *C,
    const uint N
) {
    uint k;
    uint i = get_global_id(0);
    uint j = get_global_id(1);
    float tmp;

    tmp = 0.0;
    for (k = 0; k < N; ++k)
        tmp += A[i*N+k] * B[k*N+j];
    C[i*N+j] = tmp;
}
