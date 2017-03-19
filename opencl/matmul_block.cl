__kernel void main(
    __global const float* restrict A,
    __global const float* restrict B,
    __global float* restrict C,
    __local float* restrict Awrk,
    __local float* restrict Bwrk,
    const uint n,
    const uint blksz
) {
    int kloc, Kblk;
    float Ctmp=0.0f;
    const uint i = get_global_id(0);
    const uint j = get_global_id(1);
    const uint Iblk = get_group_id(0);
    const uint Jblk = get_group_id(1);
    const uint iloc = get_local_id(0);
    const uint jloc = get_local_id(1);
    const uint nblks = n/blksz;
          uint Abase = Iblk*n*blksz;
    const uint Ainc  = blksz;
          uint Bbase = Jblk*blksz;
    const uint Binc  = blksz*n;
    for (Kblk = 0;  Kblk<nblks;  Kblk++) {
       Awrk[jloc*blksz+iloc] = A[Abase+jloc*n+iloc];
       Bwrk[jloc*blksz+iloc] = B[Bbase+jloc*n+iloc];
       barrier(CLK_LOCAL_MEM_FENCE);
       for (kloc=0; kloc<blksz; kloc++)
          Ctmp += Awrk[jloc*blksz+kloc] * Bwrk[kloc*blksz+iloc];
       barrier(CLK_LOCAL_MEM_FENCE);
       Abase += Ainc;
       Bbase += Binc;
    }
    C[j*n+i] = Ctmp;

}
