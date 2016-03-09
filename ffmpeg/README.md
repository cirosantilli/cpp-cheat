# FFmpeg

1. [Bibliography](bibliography.md)

## Introduction

<https://en.wikipedia.org/wiki/FFmpeg>

Offers a high level API to abstract multiple audio and video codecs.

Codecs are algorithms that compress audio and video.

You want to compress them to:

-   save disk space, e.g. when you save a film to disk. The container (e.g. OGG), contains a coded video file.

-   save bandwidth when it is limited. E.g. networks, USB cables (there are professional cameras that encode video to send higher quality over the cable)

    FFmpeg also takes care of breaking up the decoding into packages and sending / receiving it.

The trade-off is that you spend some CPU-time encoding/decoding, but given the huge cost of the network and storage, it is worth it.

Video / audio compression is different form that of images since multiple images can be compressed together as they differ very little between them.

FFmpeg also deals with subtitles, e.g. with `avcodec_decode_subtitle2`.

## libav

Fork because of war. Still highly compatible.

History of the fork: https://en.wikipedia.org/wiki/Libav#History

libav is going to die now that Debian switched back to FFmpeg in 2015?

`libav***` are libraries present inside of FFmpeg.

Each of those libraries can be versioned separately through the `version.h` header.

## Trivia

File stealing vulnerability January 2016: <http://news.softpedia.com/news/zero-day-ffmpeg-vulnerability-lets-anyone-steal-files-from-remote-machines-498880.shtml>

Does YouTube use it or not?

-   <http://www.streaminglearningcenter.com/blogs/youtube-uses-ffmpeg-for-encoding.html>
-   <http://multimedia.cx/eggs/googles-youtube-uses-ffmpeg/>

## Source tree

-   `AVPicture` <https://ffmpeg.org/doxygen/2.7/group__lavc__picture.html#gac1b22e9b246cb8b0928cca8f5fa524d4>

-   `AVFrame` TODO: what is meant by frame exactly in each codec type?

    Stores each plane separately, as the format is more manageable.

    You can get a raw byte array with:

        avpicture_layout

## Architecture

FFmpeg has CPU-specific acceleration optimizations on the source tree, see e.g.: `ls libavcodec`. TODO: how much is this faster?

TODO: what about GPU? `git grep -i GPU` gives some hits.
