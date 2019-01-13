/* Minimal example. Increment a vector. */

#define N 3

__global__ void inc(int *a) {
    int i = blockIdx.x;
    if (i<N) {
        a[i]++;
    }
}
