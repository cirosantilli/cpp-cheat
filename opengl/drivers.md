# Drivers

## How drivers work on Linux

To use hardware acceleration, you must do two thing:

1.  `insmod` the `.ko` kernel module provided by the vendor.

    TODO: how are those inserted by default at system startup?

1.  use the header and .so provided by the vendor.

    That `.so` will know how to talk to the kernel module.

    E.g. on Ubuntu 16.04:

        /usr/lib/nvidia-361/libGL.so
        /usr/include/nvidia-361/GL/gl.h

    If you don't, most Linux distros default to the Mesa software implementation, e.g.:

        /usr/include/GL/gl.h
        /usr/lib/x86_64-linux-gnu/libGL.so

    You can observe what your executables will load with:

        ldd ./executable

    or:


    TODO how Linux distros select between both? NVIDIA ones are not in my path, only mesa.

    But the NVIDIA driver is used by default when I compile. Looks like mesa does `dload` on NVIDIA libraries? Looks like `dlopen` is used, as strace shows several lines like;

        open("/usr/lib/nvidia-361/libGL.so.1", O_RDONLY|O_CLOEXEC) = 3

    And `ldd` says that NVIDIA is used... so the loaded library is different form that compiled against. TODO why?!

        cat /etc/ld.so.conf.d/x86_64-linux-gnu_GL.conf

    says:

        /usr/lib/nvidia-361
        /usr/lib32/nvidia-361

    which explain how that is configured.

All leading hardware implementations are currently closed source, although some open source just the kernel module (and not the `.so`) for fear of the GPL (even though Linux said closed source kernel modules are fine).

## Switch to software renderer

You have NVIDIA installed, and want to compare it to Mesa CPU renderer.

- <http://superuser.com/questions/106056/force-software-based-opengl-rendering>
- <http://unix.stackexchange.com/questions/4252/using-software-opengl-rendering-with-x>

Once you have NVIDIA installed and running, to compile with software use:

    gcc a.c -lGL -Wl,-rpath=/usr/lib/x86_64-linux-gnu/mesa

or run with:

    LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/mesa ./a

TODO: but this fails once NVIDIA is running:

    libGL error: No matching fbConfigs or visuals found
    libGL error: failed to load driver: swrast
    X Error of failed request:  GLXBadContext
      Major opcode of failed request:  154 (GLX)
      Minor opcode of failed request:  6 (X_GLXIsDirect)
      Serial number of failed request:  42
      Current serial number in output stream:  41
    X Error of failed request:  BadValue (integer parameter out of range for operation)
      Major opcode of failed request:  154 (GLX)
      Minor opcode of failed request:  24 (X_GLXCreateNewContext)
      Value in failed request:  0x0
      Serial number of failed request:  41
      Current serial number in output stream:  42
