# CUDA

NVIDIA's. More closed since controlled by NVIDIA. Also more popular for the same reason as they are the Top Dog now.

## Run on AMD

<https://www.reddit.com/r/programming/comments/49uw97/cuda_reverse_engineered_to_run_on_nonnvidia/>

<https://en.wikipedia.org/wiki/CUDA> NVIDIA's, currently only runs in NVIDIA hardware: <http://stackoverflow.com/questions/12828268/is-it-possible-to-run-cuda-on-amd-gpus>

TODO could AMD implement it legally without paying royalties to NVIDIA? Seems yes: <https://www.reddit.com/r/MachineLearning/comments/4di4os/deep_learning_is_so_dependent_on_nvidia_are_there/d1rwuxb>

Vulkan also adds the ability to run SPIR-V. So it is likely that SPIR-V will be well supported in NVIDIA and AMD cards, and we could then compile CUDA to SPIR-V. Result: AMD can run CUDA, and NVIDIA can run OpenCL.

<https://www.reddit.com/r/vulkan/comments/3snrdv/vulkan_or_opencl/>

If GPUCC generates SPIR-V, problem solved. TODO does it?

## GPUCC

LLVM-based CUDA compiler. TODO output format?

Merged into LLVM.

http://wujingyue.github.io/docs/gpucc-talk.pdf https://www.youtube.com/watch?v=JHfb8z-iSYk

http://gpuocelot.gatech.edu/ is a precursor it seems https://code.google.com/archive/p/gpuocelot/

## nvcc

<https://en.wikipedia.org/wiki/NVIDIA_CUDA_Compiler>

`--arch=sm` thing: <http://stackoverflow.com/questions/10330527/what-is-difference-between-arch-sm-13-and-arch-sm-20>

TODO: compile OpenCL: failing with:

- <http://stackoverflow.com/questions/13062469/compile-and-build-cl-file-using-nvidias-nvcc-compiler>
- <http://stackoverflow.com/questions/22730484/dont-know-what-to-do-with-nvcc-fatal-error>

## CUDA C/C++

The kernel language, like OpenCL C.

Vs ISO: http://stackoverflow.com/questions/9846523/explanation-of-cuda-c-and-c
