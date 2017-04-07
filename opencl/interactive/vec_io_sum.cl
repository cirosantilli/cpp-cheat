/* Vector sum: adds the first half of io, to the second half of io,
 * and stores it in the first half of io.
 *
 * Second half of io is untouched.
 *
 * Wasteful because half of the work items are unused,
 * but fits the generic API we need.
 * */
__kernel void kmain(__global float *io) {
    const size_t n = get_global_size(0) / 2;
    const size_t i = get_global_id(0);
    if (i < n) {
        io[i] += io[i + n];
    }
}
