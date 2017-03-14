__kernel void main(
    __global float* A,
    __global float* B,
    __global float* C,
    const uint N
)
{
    uint i = get_global_id(0);
    uint j, k;
    /* TODO remove hardcoded constant?
     * https://github.com/HandsOnOpenCL/Exercises-Solutions/issues/63
     * If I keep increasing, first:
     * - asserts on CPU fail as in: http://stackoverflow.com/questions/22083507/is-there-a-maximum-limit-to-private-memory-in-opencl
     * - CL complaing at compile time that this is too big and aborts
     **/
    float Ap[0x100000];
    float tmp;
    for (k = 0; k < N; k++)
        Ap[k] = A[i*N+k];
    for (j = 0; j < N; j++) {
        tmp = 0.0;
        for (k = 0; k < N; k++)
            tmp += Ap[k] * B[k*N+j];
        C[i*N+j] = tmp;
    }
}
