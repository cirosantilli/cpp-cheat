__kernel void kmain(
    __global float* A,
    __global float* B,
    __global float* C,
    __local float* Bcol,
    const uint n,
    const uint n_local_cols
) {
    const uint
        i = get_global_id(0),
        iloc = get_local_id(0),
        nloc = get_local_size(0)
    ;
    uint
        k,
        j,
        jloc,
        jloc_next,
        n_local_cols_left
    ;
    float
        Arow[PRIV_ROW_SIZE],
        tmp
    ;
    for (k = 0; k < n; k++)
        Arow[k] = A[i*n+k];
    j = 0;
    while (j < n) {
        n_local_cols_left = min(n_local_cols, n - j);
        for (jloc = 0; jloc < n_local_cols_left; jloc++) {
            for (k = iloc; k < n; k += nloc) {
                Bcol[k + n*jloc] = B[k*n+j+jloc];
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        for (jloc = 0; jloc < n_local_cols_left; jloc++) {
            tmp = 0.0;
            for (k = 0; k < n; k++) {
                tmp += Arow[k] * Bcol[k + n*jloc];
            }
            C[i * n + (j + jloc)] = tmp;
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        j += n_local_cols;
    }
}
