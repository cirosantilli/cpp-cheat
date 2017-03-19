__kernel void main(
    __global float* A,
    __global float* B,
    __global float* C,
    const uint N
) {
    uint i = get_global_id(0), j, k;
    float Ap[PRIV_ROW_SIZE], tmp;
    for (k = 0; k < N; k++)
        Ap[k] = A[i*N+k];
    for (j = 0; j < N; j++) {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += Ap[k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
}
