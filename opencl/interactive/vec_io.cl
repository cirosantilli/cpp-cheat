__kernel void kmain(__global float *io) {
    io[get_global_id(0)] += 1.0;
}
