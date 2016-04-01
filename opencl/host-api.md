# Host API

## clEnqueueNDRangeKernel

<https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/clEnqueueNDRangeKernel.html>

The single most important function of the API: dispatches kernels into work items and groups.

`NDRange` stands for N-Dimensional Range.

Most important arguments:

-   `work_dim`: how many dimensions will be used. Usually maximum 3 are allowed.

    E.g., if `work_dim` is 2, then each work item is identified by 2 numbers.

    TODO: why are work groups and work items treated as multi-dimensional? <http://stackoverflow.com/questions/34294133/why-are-opencl-work-groups-3-dimensional> Looks like it does not reflect in any way GPU architecture: adjacent groups don't communicate any faster, it's just to make code more readable.

    Main use cases:

    - 2D: 2D images
    - 3D: 2D images with multiple layers of information. The third dimension for example is smaller on some GPUs, as there are usually less layers than pixels.

-   `global_work_offset`: that is the first global work item ID. Default if `NULL`: `0, 0, 0, ...`.

    Each dimension of the global id can be retrieved in kernels with `get_global_id(dim)`.

-   `global_work_size`: total number of work items we want

-   `local_work_size`: how many work items will go into each work group.

    Should normally divide `global_work_size`.

    If `NULL`, OpenCL does smart things.

    This determines the value of `get_local_id` in kernels. E.g., if we have:

    - `work_dim == 1`
    - `global_work_offset == 0`
    - `global_work_size == 6`
    - `local_work_size == 3`

    Then the work item with global ID `4` has local ID 1:

        Global ID  0 1 2 3 4 5
                   |---| |---|
        Local ID   0 1 2 0 1 2

    In the past, all groups had the same number of work items, but OpenCL 2 non-uniform groups made things more complex and convenient.

## clEnqueueTask

Convenient subset of <https://www.khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clEnqueueTask.html>

Maximum one task at a time, not made for parallelism, so not very useful in practice.

## How to initialize a buffer

`clCreateBuffer` + `CL_MEM_COPY_HOST_PTR` vs. `clCreateBuffer` + `clEnqueueWriteBuffer`?

<http://stackoverflow.com/questions/3832963/two-ways-to-create-a-buffer-object-in-opencl-clcreatebuffer-vs-clcreatebuffer>
