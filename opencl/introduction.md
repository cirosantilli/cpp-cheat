# Introduction

<https://en.wikipedia.org/wiki/OpenCL#Timeline_of_vendor_implementations>

OpenCL is an open standard language which models CPU GPU computing.

It is similar to C, containing some extra keywords to model the CPU GPU world, and leaving out a few C features which GPUs cannot yet do very well.

As of 2013 its major concurrent is CUDA, which NVIDIA proprietary. Current NVIDIA do support both CUDA and OpenCL.

The OpenCL standard in maintained by the Khronos Group, the same guys who maintain OpenGL. They are an industry consortium.

OpenCL, like any other language has versions. As of 2013 the latest version is OpenCL 2.0 released in preview (unstable) as of Jul 2013.

## Implementations

<https://en.wikipedia.org/wiki/OpenCL#Implementations>

There is a certain "installable client driver loader (ICD loader)" which forwards calls to the proprietary implementation.

### Gallium Compute

<http://www.x.org/wiki/XorgEVoC/GalliumCompute/>

Looks like the major open source implementation.

### pocl

<https://github.com/pocl/pocl>

<http://portablecl.org/>

MIT and LLVM based.
