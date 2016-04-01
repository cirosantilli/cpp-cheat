# Implementations

<https://en.wikipedia.org/wiki/OpenCL#Implementations>

There is a certain "installable client driver loader (ICD loader)" which forwards calls to the proprietary implementation.

## Gallium Compute

<http://www.x.org/wiki/XorgEVoC/GalliumCompute/>

Looks like the major open source implementation.

## pocl

Portable OpenCL implementation.

<https://github.com/pocl/pocl>

<http://portablecl.org/>

MIT and LLVM based.

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

## Intel

No official Linux packages.

- <http://askubuntu.com/questions/545763/installation-of-intel-opencl>
- <http://askubuntu.com/questions/629456/intel-opencl-on-14-04>

## Altera FPGA

<https://www.altera.com/products/design-software/embedded-software-developers/opencl/overview.html>

## Transpiler

- <http://repo.or.cz/w/ppcg.git> C99 to OpenCL.
