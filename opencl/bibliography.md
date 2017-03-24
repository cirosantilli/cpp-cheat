# Bibliography

Khronos standards:

-   <https://www.khronos.org/registry/cl/>

    Qualifiers: <https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/qualifiers.html>

    Headers: <https://github.com/KhronosGroup/OpenCL-Headers>

Tutorials with sample code:

-   <https://github.com/HandsOnOpenCL/Exercises-Solutions>

    - vector addition
    - great matrix multiplication on Example 8 with multiple methods compared for speed
    - [rectangle method](https://en.wikipedia.org/wiki/Rectangle_method) integration
    - Conway's game of life.

    On Ubuntu 15.10 NVIDIA, I had to comment out some constants on `err.h`, but C worked fine.

    C++ does not compile. First it includes `CL/OpenCL.h` instead of `CL/cl.h`, and after that missing symbols.

-   <https://github.com/vpeurala/openclhelloworld> Simple hello world.

-   <https://github.com/bgaster/opencl-book-samples>, for the book OpenCL programming guide.

    The book is commercial <http://www.heterogeneouscompute.org/?page_id=5>. It is a good read. Part II has many application case studies.

    Cannot compile most examples, several OpenCL are missing in Chapter 7 on , e.g. `clCreateSubBuffer`.

-   <https://github.com/enjalot/adventures_in_opencl> TODO get working. The following might help: `sudo apt-get install libxmu-dev libxi-dev && sudo pip install pyopencl`.

-   <https://bitbucket.org/erwincoumans/opencl_course> A few examples: image rotation. Build failed with: `Error: solution '0MySolution' needs at least one project`, but if I cd into directories and do `g++ main.cpp -lOpenCL` it works mostly.

    Does platform selection based on vendor string.

Tutorials:

- <http://www.fixstars.com/en/opencl/book/OpenCLProgrammingBook> Most of it deals with setup. Does have a few concepts. Little code, and not version tracked.

Video tutorials:

- David Gohara <https://www.youtube.com/watch?v=QA483lIvL-4&list=PLTfYiv7-a3l7mYEdjk35wfY-KQj5yVXO2>

Demos:

- <https://bitbucket.org/sirbrialliance/raytrace> <https://www.youtube.com/watch?v=-5PubFKdV_w>

Resources:

- <http://developer.amd.com/tools-and-sdks/opencl-zone/opencl-resources/>
- The specifications of your hardware, e.g. <http://www.nvidia.com/object/nvs_techspecs.html>
- <http://www.cmsoft.com.br/> several good examples, but not always with full source? By <https://www.linkedin.com/in/douglas-coimbra-de-andrade-1241aa34> who is a Brazilian from a famous Brazilian university.

## NVIDIA samples

Used to be part of the GPU computing SDK, then renamed CUDA SDK.

<https://github.com/sschaetz/nvidia-opencl-examples> hosts the samples from <https://developer.nvidia.com/opencl> SDK 4.2.9, which have to be downloaded one by one!

<https://github.com/marwan-abdellah/GPU-Computing-SDK-4.2.9/> hosts a superset, but that again fails with <https://github.com/marwan-abdellah/GPU-Computing-SDK-4.2.9/issues/1>

But a header is missing and it does not compile: <https://github.com/sschaetz/nvidia-opencl-examples/issues/1>

I'm not the only one who noticed: <https://streamcomputing.eu/blog/2012-09-10/nvidias-industry-leading-support-for-opencl/>

## AMD samples

<http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk>

Come with the SDK.

Tested version 3.0. Most examples work, except a few that depend on extensions which NVIDIA didn't have.

To compile the examples:

    ln -fs /usr/lib/x86_64-linux-gnu/libOpenCL.so.1 lib/x86_64/libOpenCL.so`
    cd samples/opencl/cl/1.x
    mkdir build
    cd build
    cmake ..
    cmake --build .

Binaries fall under the `bin/` directory of each examples.

The SDK also comes with pre-built binaries under `samples/opencl/bin`. Just make sure you only run the ones whose source is under `1.x` if that's all that your implementation supports. They work fine.

License: looks like a custom MIT, you can redistribute, modify and reuse samples.

## Wrappers

-   <https://github.com/fakenmc/cf4ocl>
-   <https://github.com/RadeonOpenCompute/ROCm>
