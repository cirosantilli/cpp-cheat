__kernel void kmain(__global int *out) {
    out[get_global_id(0)]++;
}
