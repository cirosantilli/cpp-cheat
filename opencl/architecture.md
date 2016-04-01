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

Work items inside the same work group can share local memory, and can synchronize.

Work groups have a maximum size (otherwise the concept wouldn't even exist).

Ideally we would like to have a single work group for all items, as that would allow us to worry less about the location of memory on the Global / Constant / Local / Private hierarchy.

But memory localization on GPUs is important enough that OpenCL exposes this extra level.

Synchronization only works inside a single work groups: http://stackoverflow.com/questions/5895001/opencl-synchronization-between-work-groups

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

## Local and Private memory

TODO: why use those at all instead of global memory?

- <http://stackoverflow.com/questions/21872810/whats-the-advantage-of-the-local-memory-in-opencl>
- <http://stackoverflow.com/questions/9885880/effect-of-private-memory-in-opencl>

Might be faster, and global memory is limited.

HandsOnOpencl Example 8 shows how matrix multiplication becomes 10x faster with some local memory usage. Looks like memory access was the bottleneck.

It also shows how we must make an explicit copy to use private memory.

### Local memory

- <http://stackoverflow.com/questions/8888718/how-to-declare-local-memory-in-opencl>
- <http://stackoverflow.com/questions/2541929/how-do-i-use-local-memory-in-opencl>
- <http://stackoverflow.com/questions/17574570/create-local-array-dynamic-inside-opencl-kernel>
