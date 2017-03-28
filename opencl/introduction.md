# Introduction

<https://en.wikipedia.org/wiki/OpenCL>

OpenCL is an open standard language which models CPU GPU computing.

Initially created by Apple, then transferred to Khronos (thus bound to failure LOL).

It is similar to C, containing some extra keywords to model the CPU GPU world, and leaving out a few C features which GPUs cannot yet do very well.

As of 2013 its major concurrent is CUDA, which NVIDIA proprietary. Current NVIDIA do support both CUDA and OpenCL.

The OpenCL standard in maintained by the Khronos Group, the same guys who maintain OpenGL. They are an industry consortium.

OpenCL, like any other language has versions. As of 2013 the latest version is OpenCL 2.0 released in preview (unstable) as of Jul 2013.

## Versions

1.0: 2009, Apple.
1.1: 2010.
1.2: 2011.
2.0: 2013. AMD support: 2015. <http://developer.amd.com/community/blog/2015/08/26/introducing-app-sdk-30-opencl-2/>

## OpenCL and OpenGL integration

- <http://enja.org/2010/08/27/adventures-in-opencl-part-2-particles-with-opengl/>
- <http://stackoverflow.com/questions/17899514/opencl-opengl-interop-performance>
- <http://stackoverflow.com/questions/4005935/mix-opencl-with-opengl>
- <http://stackoverflow.com/questions/7907510/opengl-vs-opencl-which-to-choose-and-why>
- <http://stackoverflow.com/questions/8824269/gl-cl-interoperability-shared-texture>
- <https://github.com/9prady9/CLGLInterop> Works! Started minifying example with: <https://github.com/cirosantilli/CLGLInterop/tree/minify>
- <https://github.com/nvpro-samples/gl_cl_interop_pingpong_st> Build failed with: <https://github.com/nvpro-samples/gl_cl_interop_pingpong_st/issues/1> likely only tested on Windows.
- <https://github.com/halcy/simpleflow> VS build, fluid simulation, preview: <https://www.youtube.com/watch?v=KD2UqBCqfjA>
- <https://github.com/Twinklebear/OpenCL-OpenGL-Interop> VS build
- <http://stackoverflow.com/questions/33575715/opencl-opengl-interop-how-to-fill-a-climagegl>

Also see compute shaders for OpenGL 4.X, they seem to integrate better.

## Implement OpenGL with OpenCL:

- <https://github.com/a2flo/oclraster>
