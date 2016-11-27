# Compute

Vs OpenCL: <http://wili.cc/blog/opengl-cs.html>

Vs frament shader: <http://computergraphics.stackexchange.com/questions/54/when-is-a-compute-shader-more-efficient-than-a-pixel-shader-for-image-filterinig>

> But why did Khronos introduce compute shaders in OpenGL when they already had OpenCL and its OpenGL interoperability API? Well, OpenCL (and CUDA) are aimed for heavyweight GPGPU projects and offer more features. Also, OpenCL can run on many different types of hardware (apart from GPUs), which makes the API thick and complicated compared to light compute shaders. Finally, the explicit synchronization between OpenGL and OpenCL/CUDA is troublesome to do without crudely blocking (some of the required extensions are not even supported yet). With compute shaders, however, OpenGL is aware of all the dependencies and can schedule things smarter. This aspect of overhead might, in the end, be the most significant benefit for graphics algorithms which often execute for less than a millisecond. 

Examples:

-   <https://github.com/capnramses/antons_opengl_tutorials_book/tree/52bc6e92c10d411b8ea64e9d015a5e344a9faef8/40_compute_shader>

-   <https://www.youtube.com/watch?v=jwCAsyiYimY> <https://github.com/StanEpp/OpenGL_ParticleSystem/tree/fbe89268102aa91a7fe3f7eab5cd265292dda5cd> ported to Ubuntu 16.04 at <https://github.com/cirosantilli/OpenGL_ParticleSystem/tree/ubuntu-linux-16-04>

    Most interesting files are `ParticleSystem.cpp` and `cs.glsl`.

-   <https://community.arm.com/groups/arm-mali-graphics/blog/2014/04/17/get-started-with-compute-shaders>, runnable from their SDK

Applications:

- ray tracing
- ignore objects too far away

## Work group

TODO: what is the advantage of work groups?

Ideally, we would have a single work group, but that hits hardware design limitations (memory locality): <http://stackoverflow.com/questions/39380986/opengl-is-there-a-benefit-to-using-multiple-global-work-groups-for-compute-shad>

- http://gamedev.stackexchange.com/questions/66198/optimal-number-of-work-groups-for-compute-shaders
- https://www.cg.tuwien.ac.at/courses/Realtime/repetitorium/rtr_rep_2014_ComputeShader.pdf

More work groups does not mean faster TODO why? CL exposes `CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE`, but 

### Shared memory

Shared memory (SM).

Per work group, faster access in group. This is what characterizes different groups.

General algorithm: copy global memory to shared, and then process there.

Only useful if the given memory is accessed several times.

Same as OpenCL `local`.

TODO how efficient is it for memory access, compared to CPU memory access? Are there algorithms which are IO bound on CPU, that are not IO bound on shared memory?
