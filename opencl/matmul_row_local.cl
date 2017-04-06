__kernel void kmain(
    __global float* A,
    __global float* B,
    __global float* C,
    __local float* row,
    const uint N
) {
    uint i = get_global_id(0);
    uint j, k;
    float tmp;
    for (k = 0; k < N; k++)
        row[k] = A[i*N+k];
    for (j = 0; j < N; j++) {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += row[k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
}
