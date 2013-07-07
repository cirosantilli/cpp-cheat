#dependencies

Relies on POSIX 7 utilities such as `make`, `sh`, `cp`, etc.

Non-POSIX dependencies:
	
- g++
- all the opencv libraries listed on the makefile `LIBS` variable in the library search path
- `<opencv2/opencv.hpp>` in the header search path

There may be an automated installation procedure for your system via targets of type: `make install-deps-SYSTEM`, for example `install-deps-ubuntu`.

##test opencv is working

If something goes wrong, you will want to first test that OpenCV is working properly.

You can do that by running the example files

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
