# Concepts

Hierarchy from top to bottom:

- Host: the entire system
- Device group: multiple devices, e.g. one GPU and one CPU.
- Compute device
- Compute unit
- Processing element
- Work group
- Work item

## TODO

GPU vs CPU hardware level.

<https://youtu.be/e-2bTxKuS2U?list=PLTfYiv7-a3l7mYEdjk35wfY-KQj5yVXO2&t=319> mentions GPU has no cache.

## Platform

TODO what is a platform?

<http://stackoverflow.com/questions/3444664/does-any-opencl-host-have-more-than-one-platform>

## Compute device

One CPU, one GPU, etc.

## Compute unit

TODO vs core?

Can be obtained with: `clGetDeviceInfo(CL_DEVICE_MAX_COMPUTE_UNITS)`

## Processing element

TODO

## Work group

Contains many work items.

Is basically a completely independent chunk of work.

Work items inside the same work group can share local memory, and can synchronize.

So ideally, we would like to have a single work group, with infinitely many work items inside it.

However, the laws of physics are cruel, and the following limits exist:

- `CL_DEVICE_MAX_WORK_GROUP_SIZE`: maximum number of work items inside the work group
- `CL_DEVICE_MAX_WORK_ITEM_SIZES[CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS]`: maximum  number of work items on each dimension

This is due to memory localization on GPUs is important enough that OpenCL exposes this extra level.

We can however has as many work groups as we want.

Synchronization only works inside a single work groups: <http://stackoverflow.com/questions/5895001/opencl-synchronization-between-work-groups>

### Local size

Size of the work group.

On CPU: always 1. TODO why?

On GPU; must divide Global size.

### Uniform work group

### Non-uniform work group

Work groups with different sizes.

Application: take care of edge cases of the data, e.g. image edges: <https://software.intel.com/en-us/articles/opencl-20-non-uniform-work-groups>

## Work item

Each work item runs your kernel code in parallel to the other ones.

An work item can be seen as a thread.

Contains private memory, which no other work item can see.

TODO: can a single work item be run in parallel on the GPU?

## Local memory

## Private memory

- <http://stackoverflow.com/questions/9885880/effect-of-private-memory-in-opencl>
- <http://stackoverflow.com/questions/9885880/is-private-memory-slower-than-local-memory>

TODO: can private memory be slower than local memory? <http://stackoverflow.com/questions/21872810/whats-the-advantage-of-the-local-memory-in-opencl>

Might be faster, and global memory is limited.

HandsOnOpencl Example 8 shows how matrix multiplication becomes 10x faster with some local memory usage. Looks like memory access was the bottleneck.

It also shows how we must make an explicit copy to use private memory.

### Local memory

- <http://stackoverflow.com/questions/8888718/how-to-declare-local-memory-in-opencl>
- <http://stackoverflow.com/questions/2541929/how-do-i-use-local-memory-in-opencl>
- <http://stackoverflow.com/questions/17574570/create-local-array-dynamic-inside-opencl-kernel>

## Pinned memory

TODO.

- <http://stackoverflow.com/questions/25496656/cl-mem-use-host-ptr-vs-cl-mem-copy-host-ptr-vs-cl-mem-alloc-host-ptr>
- <http://stackoverflow.com/questions/24158909/how-to-use-pinned-memory-mapped-memory-in-opencl>
