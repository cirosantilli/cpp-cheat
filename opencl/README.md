# OpenCL

OpenCL is an open standard language which models CPU GPU computing.

It is similar to C, containing some extra keywords to model the CPU GPU world, and leaving out a few C features which GPUs cannot yet do very well.

As of 2013 its major concurrent is CUDA, which NVIDIA proprietary. Current NVIDIA do support both CUDA and OpenCL.

The OpenCL standard in maintained by the Khronos Group, the same guys who maintain OpenGL. They are an industry consortium.

OpenCL, like any other language has versions. As of 2013 the latest version is OpenCL 2.0 released in preview (unstable) as of Jul 2013.

## Install

The first step is to get you GPU working. Good luck on that, specially if you are on Linux =)

Next, you will need an SDK developed by the GPU vendor. There is no fixed standard assembly language for GPUs, in part because GPUs are changing very fast, so vendors do not want to get tied down to an interface. Therefore, the only way to go is to pass through the vendor SDK which should implement OpenCL.
