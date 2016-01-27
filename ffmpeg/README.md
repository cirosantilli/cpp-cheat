# FFmpeg

<https://en.wikipedia.org/wiki/FFmpeg>

Offers a high level API to abstract multiple codecs.

Codecs are algorithms that compress audio and video.

You want to compress them to:

-   save disk space, e.g. when you save a film to disk. The container (e.g. OGG), contains a coded video file.

-   save bandwidth when it is limited. E.g. networks, USB cables (there are professional cameras that encode video to send higher quality over the cable)

    FFmpeg also takes care of breaking up the decoding into packages and sending / receiving it.

Video / audio compression is different form that of images since multiple images can be compressed together as they differ very little between them.

## libav

Fork because of war. Still highly compatible.

History of the fork: https://en.wikipedia.org/wiki/Libav#History

libav is going to die now that Debian switched back to FFmpeg.
