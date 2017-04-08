__kernel void kmain(
    __global float* A,
    __global float* B,
    __global float* C,
    const uint N
) {
    uint i = get_global_id(0), j, k;
    float Arow[PRIV_ROW_SIZE], tmp;

    /* Cache the row to private memory. */
    for (k = 0; k < N; k++)
        Arow[k] = A[i*N+k];

    for (j = 0; j < N; j++) {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += Arow[k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
}
