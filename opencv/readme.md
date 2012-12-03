#install ubuntu 12.04

    sudo aptitude install build-essential
    sudo aptitude install libopencv-dev opencv-doc

not sure the following  are needed in general:

    sudo aptitude install libavformat-dev
    sudo aptitude install ffmpeg
    sudo aptitude install libcv2.1 libcvaux2.1 libhighgui2.1 python-opencv opencv-doc libcv-dev libcvaux-dev libhighgui-dev

##test install

now copy the examples and compile run them:

    cp -r /usr/share/doc/opencv-doc/examples ./
    cd examples/c
    ./build-all.sh

#using

##there are 2 versions

opencv2 is the second version released in 2009,

this is why you have both folders ``/usr/include/opencv`` and ``/usr/include/opencv2``

for new projects, use opencv2 only

##include

the only header needed is ``opencv2/opencv.hpp`` which includes all the others

you can also include the subparts individually.

note that:

    pkg-config opencv --cflags

only includes opencv, so it seems that to use opencv2,
you have to

    #include <opencv2/opencv.hpp>
