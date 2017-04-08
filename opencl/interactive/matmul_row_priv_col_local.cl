__kernel void kmain(
    __global float* A,
    __global float* B,
    __global float* C,
    __local float* Bcol,
    const uint n
) {
    uint
        i = get_global_id(0),
        iloc = get_local_id(0),
        nloc = get_local_size(0),
        k,
        j
    ;
    float
        Arow[PRIV_ROW_SIZE],
        tmp
    ;
    /* Cache the row to private memory. */
    for (k = 0; k < n; k++)
        Arow[k] = A[i*n+k];

    for (j = 0; j < n; j++) {

        /* Cache the col to local memory,
         * a little with each work item. */
        for (k = iloc; k < n; k += nloc)
            Bcol[k] = B[k*n+j];

        /* All work items must be done copying to
         * local memory before we proceed, or the B column,
         * which all A rows use, will only be half loaded. */
        barrier(CLK_LOCAL_MEM_FENCE);

        /* Actually do the multiplicaiton using our caches. */
        tmp = 0.0;
        for (k = 0; k < n; k++)
            tmp += Arow[k] * Bcol[k];
        C[i*n+j] = tmp;

        /* All operations must be done before
            * we start fetching the next B column. */
        barrier(CLK_LOCAL_MEM_FENCE);
    }
}
