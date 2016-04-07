# Alternatives

As of 2016, CUDA is the top cat.

## OpenMP

<http://stackoverflow.com/questions/7263193/opencl-performance-vs-openmp>

Directive based: you write stuff like:

http://stackoverflow.com/questions/19494786/openacc-vs-openmp-mpi-differences

    /* Fork a team of threads giving them their own copies of variables */
    #pragma omp parallel private(nthreads, tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num();

instead of compiling a kernel.

## OpenACC

<https://en.wikipedia.org/wiki/OpenACC>

NVIDIA's OpenMP, similar to OpenMP: <http://stackoverflow.com/questions/19494786/openacc-vs-openmp-mpi-differences>

## RenderScript

Google's choice for Android: <http://stackoverflow.com/questions/14385843/why-did-google-choose-renderscript-instead-of-opencl>

Google somewhat opposes OpenCL, maybe because it was created by Apple?

## Metal

<https://en.wikipedia.org/wiki/Metal_%28API%29>

Apple's response to Google's RenderScript.

## DirectX

Microsoft, Windows, Xbox.

## Cilk

<https://en.wikipedia.org/wiki/Cilk>

Intel's

## DirectCompute

<https://en.wikipedia.org/wiki/DirectCompute>

Microsoft's

## Unified parallel C

<https://en.wikipedia.org/wiki/Unified_Parallel_C>

## Compute shaders

OpenGL compute shaders <http://stackoverflow.com/questions/15868498/what-is-the-difference-between-opencl-and-opengls-compute-shader>

Easier to integrate with graphics stuff.
