# Introduction

<https://en.wikipedia.org/wiki/OpenCL>

OpenCL is an open standard language which models CPU GPU computing.

Initially created by Apple, then transferred to Khronos (thus bound to failure LOL).

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

Portable OpenCL implementation.

<https://github.com/pocl/pocl>

<http://portablecl.org/>

MIT and LLVM based.

## Tools

- <http://repo.or.cz/w/ppcg.git> C99 to OpenCL.

## Alternatives

- <https://en.wikipedia.org/wiki/CUDA> NVIDIA's
- OpenMP <http://stackoverflow.com/questions/7263193/opencl-performance-vs-openmp>
- <https://en.wikipedia.org/wiki/Cilk> Intel's
- <https://en.wikipedia.org/wiki/DirectCompute> Microsoft's
- <https://en.wikipedia.org/wiki/Unified_Parallel_C>

## OpenCL + OpenGL for real time rendering of complex calculations

- <http://stackoverflow.com/questions/4005935/mix-opencl-with-opengl>
- <http://enja.org/2010/08/27/adventures-in-opencl-part-2-particles-with-opengl/>
