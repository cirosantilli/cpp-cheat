# OpenCV

## Test OpenCV is working

If something goes wrong, you will want to first test that OpenCV is working properly.

You can do that by running the example files

    cp -r /usr/share/doc/opencv-doc/examples ./
    cd examples/c
    ./build-all.sh

## Usage

There are 2 versions of OpenCV.

OpenCV 2 is the second version released in 2009.

This is why you have both folders `/usr/include/opencv` and `/usr/include/opencv2`.

For new projects, use OpenCV 2 only.

### Headers

The only header needed is `opencv2/opencv.hpp` which includes all the others.

Note that:

    pkg-config opencv --cflags

Only includes `opencv`, so it seems that to use `opencv2`, you have to

    #include <opencv2/opencv.hpp>
