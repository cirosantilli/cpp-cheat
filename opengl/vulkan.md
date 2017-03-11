# Vulkan

<https://en.wikipedia.org/wiki/Vulkan_%28API%29>

Also by Khronos.

<http://gamedev.stackexchange.com/questions/96014/what-is-vulkan-and-how-does-it-differ-from-opengl>

Derived from <https://en.wikipedia.org/wiki/Mantle_%28API%29> by AMD, now abandoned in favor of Vulkan, and will somewhat be the new OpenGL.

There is no ES version like for OpenGL, <http://arstechnica.com/gadgets/2015/08/android-to-support-vulkan-graphics-api-the-open-answer-to-metal-and-dx12/> says ES and non-ES convergence has been going on for a while now.

TODO software implementations: <https://www.quora.com/unanswered/Is-there-a-Vulkan-software-CPU-implementation>

## Examples

- <https://github.com/SaschaWillems/Vulkan>. Tons of examples, best collection so far. Tested on Ubuntu host Android target. Linux build only exists for some examples, but porting is trivial: <https://github.com/SaschaWillems/Vulkan/issues/297#issuecomment-284665246>
- <https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers>. Cube only. Tested on Ubuntu host, Android target.
- <https://github.com/LunarG/VulkanSamples> Basically same as `Vulkan-LoaderAndValidationLayers`. TODO why?
- <https://github.com/Overv/VulkanTutorial>
- <https://gist.githubusercontent.com/sheredom/523f02bbad2ae397d7ed255f3f3b5a7f/raw/7c33ee6136ae1f7c03741ba7ad6e02e8de9f9802/VkComputeSample> Codeplay employee writes SPIR-V shader by hand! :-) The absolute minimal example?
- <https://github.com/googlesamples/android-vulkan-tutorials> Cube only. Didn't work.

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

## OpenGL implemented with Vulkan

<https://github.com/g-truc/glo>
