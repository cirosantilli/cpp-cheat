# Build

How to build and use `ffmpeg`.

    ./configure
    make

Examples:

    make examples
    cd doc/examples
    ./some-example

- `decoding_encoding.c`: generate synthetic audio and video, encode and decode
- `muxing.c`: generate synthetic audio and video, and put them together into a single container output file. Detects format from file extension with `avformat_alloc_output_context2`.

## Codecs

Only a few codecs are included by default.

Build with `H264` support:

    sudo apt-get install libx264-dev
	./configure \
		--enable-gpl \
	    --enable-parser=h264 \
		--enable-libx264 \
		--enable-encoder=libx264 \
		--enable-decoder=h264

`--enable-gpl` is required here, because `libx264` <http://www.videolan.org/developers/x264.html> from VideoLAN is GPL. I think this option excludes non-GPL compatible codecs. Lol, this domain is so patent ridden that it is necessary to manage that from the build script. See also: <https://www.ffmpeg.org/legal.html>

The following options also seem interesting: TODO what do they do?

`--enable-gpl --enable-version3 --enable-nonfree --enable-libvpx --enable-libvorbis`
