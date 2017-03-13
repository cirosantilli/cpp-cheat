# Applications

For an application to experience speedup compared to the CPU, it must:

- be highly parallelizable
- do a lot of work per input byte, because IO is very expensive

Minimal example request: <http://stackoverflow.com/questions/7663343/simplest-possible-example-to-show-gpu-outperform-cpu-using-cuda>

## Examples

-   Monte Carlo

-   PDEs

    - <https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model>
    - Reverse Time Migration: RTM <http://www.slb.com/services/seismic/geophysical_processing_characterization/dp/technologies/depth/prestackdepth/rtm.aspx>

-   clMathLibraries organization, by AMD employees

    -   <https://github.com/clMathLibraries/clFFT> FFT
    -   <https://github.com/clMathLibraries/clRNG> random number generation

### Matrix multiplication

- <http://hpclab.blogspot.fr/2011/09/is-gpu-good-for-large-vector-addition.html>
- <https://developer.nvidia.com/cublas>
- <https://github.com/clMathLibraries/clBLAS>
- <https://github.com/clMathLibraries/clSPARSE>
- <http://stackoverflow.com/questions/16748604/opencl-matrix-multiplication-should-be-faster>
- <http://stackoverflow.com/questions/33086029/multiply-matrices-in-c-or-in-glsl>

Not surprising, since rendering is just a bunch of matrix multiplications, with fixed matrices and varying vectors.

Sparse: <http://stackoverflow.com/questions/3438826/sparse-matrix-multiplication-on-gpu-or-cpu>

Bolt: C++ STL GPU powered implementation by AMD: <http://developer.amd.com/tools-and-sdks/opencl-zone/bolt-c-template-library/> Other suggestions: <http://stackoverflow.com/questions/16438099/high-level-gpu-programming-in-c>

## Non-applications

Vector addition. Too little work per input byte (1 CPU cycle). <https://forums.khronos.org/showthread.php/7741-CPU-faster-in-vector-addition-than-GPU>, <http://stackoverflow.com/questions/15194798/vector-step-addition-slower-on-cuda> <http://hpclab.blogspot.fr/2011/09/is-gpu-good-for-large-vector-addition.html>

## Projects using OpenCL

Notable users:

- OpenCV
- Bullet physics
- VP9 decoding 2013 by Ittiam: <http://malideveloper.arm.com/partner-showroom/ittiam-vp9-decoder-using-opencl/>
