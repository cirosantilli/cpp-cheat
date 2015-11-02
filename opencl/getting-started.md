# Getting started

## NVIDIA

On Ubuntu 15.10 with an NVIDIA NVS 5400M, Lenovo T430:

    sudo apt-get install nvidia-352 nvidia-352-dev nvidia-prime
    sudo ln -s /usr/include/nvidia-352/GL /usr/local/include
    sudo ln -s /usr/lib/x86_64-linux-gnu/libOpenCL.so.1 /usr/local/lib/libOpenCL.so

Then compile with:

	gcc -o main main.c -lOpenCL

Notes:

- find your GPU model: <http://askubuntu.com/questions/72766/how-do-i-find-out-the-model-of-my-graphics-card>
- test that the driver is working: <http://askubuntu.com/questions/68028/how-do-i-check-if-ubuntu-is-using-my-nvidia-graphics-card>
- do not install the `nvidia-current` package. It is old. Either `apt-cache search nvidia` and get the latest one, or use `software-properties-gtk` "Additional Drivers" tab.
