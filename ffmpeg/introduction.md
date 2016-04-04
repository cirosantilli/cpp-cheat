# Introduction

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
