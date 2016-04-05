/*
Basis for:

http://stackoverflow.com/questions/16667687/how-to-convert-rgb-from-yuv420p-for-ffmpeg-encoder
http://stackoverflow.com/questions/2940671/how-does-one-encode-a-series-of-images-into-h264-using-the-x264-c-api/36405714#36405714
http://stackoverflow.com/questions/16667687/how-to-convert-rgb-from-yuv420p-for-ffmpeg-encoder

Transform a bunch of raw pixels into compressed video formats.

Those formats are not muxed into a container format,
the muxing examples hows how to do that:
https://github.com/FFmpeg/FFmpeg/blob/n3.0/doc/examples/muxing.c

You can then view the videos with VLC or some other player (which contain decoders).

Adapted from:
https://github.com/FFmpeg/FFmpeg/blob/4b150fbe1f3905f8245f63d74ff72f2ef92d9717/doc/examples/decoding_encoding.c
but modified to:

- split up constructors and destructors for easier inclusion in other projects
- take rgb input instead of YUV
*/

#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>

static AVCodecContext *c = NULL;
static AVFrame *frame;
static AVPacket pkt;
static FILE *file;
static struct SwsContext *sws_context = NULL;

/*
Convert RGB24 array to YUV. Save directly to the `frame`,
modifying its `data` and `linesize` fields
*/
static void ffmpeg_encoder_set_frame_yuv_from_rgb(uint8_t *rgb) {
    const int in_linesize[1] = { 3 * c->width };
    sws_context = sws_getCachedContext(sws_context,
            c->width, c->height, AV_PIX_FMT_RGB24,
            c->width, c->height, AV_PIX_FMT_YUV420P,
            0, 0, 0, 0);
    sws_scale(sws_context, (const uint8_t * const *)&rgb, in_linesize, 0,
            c->height, frame->data, frame->linesize);
}

/*
Generate 2 different images with four colored rectangles, each 25 frames long:

Image 1:

    black | red
    ------+-----
    green | blue

Image 2:

    yellow | red
    -------+-----
    green  | white
*/
void generate_rgb(int width, int height, int pts, uint8_t **rgbp) {
    int x, y, cur;
    uint8_t *rgb = *rgbp;
    rgb = realloc(rgb, 3 * sizeof(uint8_t) * height * width);
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            cur = 3 * (y * width + x);
            rgb[cur + 0] = 0;
            rgb[cur + 1] = 0;
            rgb[cur + 2] = 0;
            if ((frame->pts / 25) % 2 == 0) {
                if (y < height / 2) {
                    if (x < width / 2) {
                        /* Black. */
                    } else {
                        rgb[cur + 0] = 255;
                    }
                } else {
                    if (x < width / 2) {
                        rgb[cur + 1] = 255;
                    } else {
                        rgb[cur + 2] = 255;
                    }
                }
            } else {
                if (y < height / 2) {
                    rgb[cur + 0] = 255;
                    if (x < width / 2) {
                        rgb[cur + 1] = 255;
                    } else {
                        rgb[cur + 2] = 255;
                    }
                } else {
                    if (x < width / 2) {
                        rgb[cur + 1] = 255;
                        rgb[cur + 2] = 255;
                    } else {
                        rgb[cur + 0] = 255;
                        rgb[cur + 1] = 255;
                        rgb[cur + 2] = 255;
                    }
                }
            }
        }
    }
    *rgbp = rgb;
}

/* Allocate resources and write header data to the output file. */
void ffmpeg_encoder_start(const char *filename, int codec_id, int fps, int width, int height) {
    AVCodec *codec;
    int ret;
    avcodec_register_all();
    codec = avcodec_find_encoder(codec_id);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }
    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }
    c->bit_rate = 400000;
    c->width = width;
    c->height = height;
    c->time_base.num = 1;
    c->time_base.den = fps;
    c->gop_size = 10;
    c->max_b_frames = 1;
    c->pix_fmt = AV_PIX_FMT_YUV420P;
    if (codec_id == AV_CODEC_ID_H264)
        av_opt_set(c->priv_data, "preset", "slow", 0);
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }
    file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
    frame->format = c->pix_fmt;
    frame->width  = c->width;
    frame->height = c->height;
    ret = av_image_alloc(frame->data, frame->linesize, c->width, c->height, c->pix_fmt, 32);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate raw picture buffer\n");
        exit(1);
    }
}

/*
Write trailing data to the output file
and free resources allocated by ffmpeg_encoder_start.
*/
void ffmpeg_encoder_finish(void) {
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    int got_output, ret;
    do {
        fflush(stdout);
        ret = avcodec_encode_video2(c, &pkt, NULL, &got_output);
        if (ret < 0) {
            fprintf(stderr, "Error encoding frame\n");
            exit(1);
        }
        if (got_output) {
            fwrite(pkt.data, 1, pkt.size, file);
            av_packet_unref(&pkt);
        }
    } while (got_output);
    fwrite(endcode, 1, sizeof(endcode), file);
    fclose(file);
    avcodec_close(c);
    av_free(c);
    av_freep(&frame->data[0]);
    av_frame_free(&frame);
}

/*
Encode one frame from an RGB24 input and save it to the output file.
Must be called after ffmpeg_encoder_start, and ffmpeg_encoder_finish
must be called after the last call to this function.
*/
void ffmpeg_encoder_encode_frame(uint8_t *rgb) {
    int ret, got_output;
    ffmpeg_encoder_set_frame_yuv_from_rgb(rgb);
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;
    ret = avcodec_encode_video2(c, &pkt, frame, &got_output);
    if (ret < 0) {
        fprintf(stderr, "Error encoding frame\n");
        exit(1);
    }
    if (got_output) {
        fwrite(pkt.data, 1, pkt.size, file);
        av_packet_unref(&pkt);
    }
}

/* Represents the main loop of an application which generates one frame per loop. */
static void encode_example(const char *filename, int codec_id) {
    int pts;
    int width = 320;
    int height = 240;
    uint8_t *rgb = NULL;
    ffmpeg_encoder_start(filename, codec_id, 25, width, height);
    for (pts = 0; pts < 100; pts++) {
        frame->pts = pts;
        generate_rgb(width, height, pts, &rgb);
        ffmpeg_encoder_encode_frame(rgb);
    }
    ffmpeg_encoder_finish();
    free(rgb);
}

int main(void) {
    encode_example("tmp.h264", AV_CODEC_ID_H264);
    encode_example("tmp.mpg", AV_CODEC_ID_MPEG1VIDEO);
    /* TODO: is this encoded correctly? Possible to view it without container? */
    /*encode_example("tmp.vp8", AV_CODEC_ID_VP8);*/
    return 0;
}
