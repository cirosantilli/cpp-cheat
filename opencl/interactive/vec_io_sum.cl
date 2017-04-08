/* Vector sum: add the first half of io, to the second half of io,
 * and stores it in the first half of io.
 *
 * Second half of io is untouched.
 *
 * To be less wasteful, you should set the work group size to n / 2,
 * but as we know, vector sum cannot be sped up by the GPU
 * in the first place, so it won't matter much.
 * */
__kernel void kmain(__global float *io) {
    const size_t n = get_global_size(0) / 2;
    const size_t i = get_global_id(0);
    if (i < n) {
        io[i] += io[i + n];
    }
}
