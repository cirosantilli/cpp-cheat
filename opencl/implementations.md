# Implementations

<https://en.wikipedia.org/wiki/OpenCL#Implementations>

## ICD

## Installable client driver

There is a certain "installable client driver loader (ICD loader)" which forwards calls to the proprietary implementation.

<https://www.khronos.org/news/permalink/opencl-installable-client-driver-icd-loader>

TODO how to use it.

## Gallium Compute

<http://www.x.org/wiki/XorgEVoC/GalliumCompute/>

Looks like the major open source implementation. MIT and LLVM based.

## NVIDIA

Implements it, but way after CUDA features.

- <http://stackoverflow.com/questions/20086153/is-there-a-way-to-upgrade-to-opencl-2-0>
- <https://streamcomputing.eu/blog/2012-09-10/nvidias-industry-leading-support-for-opencl/>

Likely their monopoly + anti antitrust tactic.

Offers official Ubuntu packages as of 15.10.

TODO why are many symbols missing even though NVIDIA claims to support a given OpenCL version?

- `clCreateSubBuffer`
- `clEnqueueReadBufferRect`

Threads:

- <https://devtalk.nvidia.com/default/topic/572548/support-for-opencl-1-2-gtx-690-ubuntu>
- <http://stackoverflow.com/questions/3271243/clcreatesubbuffer-not-found-oo>
- <https://devtalk.nvidia.com/default/topic/486564/nvidia-39-s-opencl-1-1-and-clcreatesubbuffer/>

OpenCL 2 announced in 2017:

- <http://stackoverflow.com/questions/29219307/opencl-2-0-on-nvidia-graphics-cards>
- <https://devtalk.nvidia.com/default/topic/954622/opencl-2-x-support-plans-/>

but hardware support will very likely be / is already there because of Vulkan / OpenCL 2 convergence.

OpenCL 1.2 apparently added in driver 350.12, on Kepler hardware and up.

## Intel

<http://stackoverflow.com/questions/19141272/opencl-implementation-for-intel-core-i5-linux>

No official Linux packages.

- <http://askubuntu.com/questions/545763/installation-of-intel-opencl>
- <http://askubuntu.com/questions/629456/intel-opencl-on-14-04>

Beignet looks like an open source implementation for Intel's embedded GPU: <https://www.freedesktop.org/wiki/Software/Beignet/> TODO reversed or documented?

## Altera FPGA

<https://www.altera.com/products/design-software/embedded-software-developers/opencl/overview.html>

## Transpiler

- <http://repo.or.cz/w/ppcg.git> C99 to OpenCL.

## CPU implementations

## Software implementations

Slow but portable, and a sanity check that OpenCL is actually making anything faster:

### Clover

- <https://people.freedesktop.org/~steckdenis/clover/>

### pocl

Portable OpenCL implementation.

<https://github.com/pocl/pocl>

<http://portablecl.org/>

### Oclgrind

<https://github.com/jrprice/Oclgrind>
