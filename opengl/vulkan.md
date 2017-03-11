# Vulkan

<https://en.wikipedia.org/wiki/Vulkan_%28API%29>

Also by Khronos.

<http://gamedev.stackexchange.com/questions/96014/what-is-vulkan-and-how-does-it-differ-from-opengl>

Derived from <https://en.wikipedia.org/wiki/Mantle_%28API%29> by AMD, now abandoned in favor of Vulkan, and will somewhat be the new OpenGL.

There is no ES version like for OpenGL, <http://arstechnica.com/gadgets/2015/08/android-to-support-vulkan-graphics-api-the-open-answer-to-metal-and-dx12/> says ES and non-ES convergence has been going on for a while now.

TODO software implementations: <https://www.quora.com/unanswered/Is-there-a-Vulkan-software-CPU-implementation>

## Samples

- <https://github.com/SaschaWillems/Vulkan>
- <https://github.com/LunarG/VulkanSamples>
- <https://github.com/Overv/VulkanTutorial>
- <https://gist.githubusercontent.com/sheredom/523f02bbad2ae397d7ed255f3f3b5a7f/raw/7c33ee6136ae1f7c03741ba7ad6e02e8de9f9802/VkComputeSample> Codeplay employee writes SPIR-V shader by hand! :-) The absolute minimal example?

## Hardware support

Supported hardware:

- NVIDIA <https://developer.nvidia.com/vulkan-driver>: Kepler and Maxwell
- Android
    - API 24?
    - Samsung Galaxy S7 was the first to support it.

Works on most GPUs that support OpenGL ES 3.1 <http://arstechnica.com/gadgets/2015/08/android-to-support-vulkan-graphics-api-the-open-answer-to-metal-and-dx12/>

## Ubuntu install

TODO. Already had an NVIDIA NVS 5400M driver 361.42 working for OpenGL.

- <http://askubuntu.com/questions/774131/installing-nvidia-vulkan-drivers-for-16-04>
- <https://github.com/SaschaWillems/Vulkan/issues/188>
