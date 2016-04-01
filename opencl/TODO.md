# TODO

1. synchronization, work_group_barrier https://www.khronos.org/registry/cl/sdk/2.1/docs/man/xhtml/work_group_barrier.html || http://stackoverflow.com/questions/7673990/in-opencl-what-does-mem-fence-do-as-opposed-to-barrier https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/mem_fence.html `mem_fence` (TODO not in OpenCL 2?)
1. images
1. local and private memory to optimize things. Done in HandsOnOpenCL exercise 8 chapter 21 of 2011 OpenCL programming guide.
1. create a bunch of educational and actually useful examples where GPU owns CPU and time them 
1. understand why kernels / work items / groups are SIMD, even if they seem completely independent. How does it work? They can only be parallel is the same instruction is to be used on all kernels at once? What breaks it's efficiency? Branching clearly does: we could do an `switch (get_global_id())` and have completely different code running on each kernel. Looks like that is correct: https://news.ycombinator.com/item?id=1969631 | http://stackoverflow.com/questions/5897454/conditionals-in-gpu-programming
1. how much parallelism do GPUs actually have? http://stackoverflow.com/questions/6490572/cuda-how-many-concurrent-threads-in-total | http://gamedev.stackexchange.com/questions/17243/how-many-parallel-units-does-a-gpu-have Depends on what that means, data parallelism? Don't forge that CPU's have 4 wide SIMD nowadays.
