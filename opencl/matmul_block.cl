__kernel void kmain(
    __global const float* restrict A,
    __global const float* restrict B,
    __global float* restrict C,
    __local float* restrict Aloc,
    __local float* restrict Bloc,
    const uint n,
    const uint blksz
) {
    const uint
        iloc = get_local_id(0),
        jloc = get_local_id(1),
        nblks = n / blksz,
        b_inc = blksz * n
    ;
    float c_tmp = 0.0;
    uint
        a_base = get_group_id(1) * blksz * n,
        b_base = get_group_id(0) * blksz,
        iload,
        iload_loc,
        kloc,
        kblk
    ;
    for (kblk = 0; kblk < nblks; kblk++) {
        iload_loc = jloc * blksz + iloc;
        iload = jloc * n + iloc;
        Aloc[iload_loc] = A[a_base + iload];
        Bloc[iload_loc] = B[b_base + iload];
        barrier(CLK_LOCAL_MEM_FENCE);
        for (kloc = 0; kloc < blksz; kloc++)
           c_tmp += Aloc[jloc * blksz + kloc] * Bloc[kloc * blksz + iloc];
        barrier(CLK_LOCAL_MEM_FENCE);
        a_base += blksz;
        b_base += b_inc;
    }
    C[get_global_id(1) * n + get_global_id(0)] = c_tmp;
}
