__kernel void kmain(__global uint *out) {
    out[0] = get_work_dim();

    /* Total number of work items that will run this kernel, not the size of each one...
     * I don't think you can get the size of each one here, just calculate it on CPU
     * and pass as a const uint paremeter. */
    out[1] = get_global_size(0);

    /* Unique global ID of the current work item. */
    out[2] = get_global_id(0);

    /* Number of work items in this group. */
    out[3] = get_local_size(0);

    /* Local ID of this work item inside this work group. */
    out[4] = get_local_id(0);

    /* How many work groups will execute this kernel, == global_size / local_size */
    out[5] = get_num_groups(0);

    /* Current group. */
    out[6] = get_group_id(0);

    /* Global offset passed on to NDrange. */
    out[7] = get_global_offset(0);
}
