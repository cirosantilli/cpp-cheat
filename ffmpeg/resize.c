/*
http://stackoverflow.com/questions/12831761/how-to-resize-a-picture-using-ffmpegs-sws-scale/36487785#36487785
*/

#include "common.h"

static AVCodecContext *c = NULL;
static AVFrame *frame;
static AVFrame *frame2;
static AVPacket pkt;
static FILE *file;
static struct SwsContext *sws_context = NULL;

static void ffmpeg_encoder_init_frame(AVFrame **framep, int width, int height) {
    int ret;
    AVFrame *frame;
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
    frame->format = c->pix_fmt;
    frame->width  = width;
    frame->height = height;
    ret = av_image_alloc(frame->data, frame->linesize, frame->width, frame->height, frame->format, 32);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate raw picture buffer\n");
        exit(1);
    }
    *framep = frame;
}

static void ffmpeg_encoder_scale(void) {
    sws_context = sws_getCachedContext(sws_context,
            frame->width, frame->height, AV_PIX_FMT_YUV420P,
            frame2->width, frame2->height, AV_PIX_FMT_YUV420P,
            SWS_BICUBIC, NULL, NULL, NULL);
    sws_scale(sws_context, (const uint8_t * const *)frame->data, frame->linesize, 0,
            frame->height, frame2->data, frame2->linesize);
}

static void ffmpeg_encoder_set_frame_yuv_from_rgb(uint8_t *rgb) {
    const int in_linesize[1] = { 3 * frame->width };
    sws_context = sws_getCachedContext(sws_context,
            frame->width, frame->height, AV_PIX_FMT_RGB24,
            frame->width, frame->height, AV_PIX_FMT_YUV420P,
            0, NULL, NULL, NULL);
    sws_scale(sws_context, (const uint8_t * const *)&rgb, in_linesize, 0,
            frame->height, frame->data, frame->linesize);
}

void ffmpeg_encoder_start(const char *filename, int codec_id, int fps, int width, int height, float factor) {
    AVCodec *codec;
    int width2 = width * factor;
    int height2 = height * factor;
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
    c->width = width2;
    c->height = height2;
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
    ffmpeg_encoder_init_frame(&frame, width, height);
    ffmpeg_encoder_init_frame(&frame2, width2, height2);
}

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
    av_freep(&frame2->data[0]);
    av_frame_free(&frame2);
}

void ffmpeg_encoder_encode_frame(uint8_t *rgb) {
    int ret, got_output;
    ffmpeg_encoder_set_frame_yuv_from_rgb(rgb);
    ffmpeg_encoder_scale();
    frame2->pts = frame->pts;
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;
    ret = avcodec_encode_video2(c, &pkt, frame2, &got_output);
    if (ret < 0) {
        fprintf(stderr, "Error encoding frame\n");
        exit(1);
    }
    if (got_output) {
        fwrite(pkt.data, 1, pkt.size, file);
        av_packet_unref(&pkt);
    }
}

static void encode_example(int width, int height, float factor) {
    char filename[255];
    int pts;
    uint8_t *rgb = NULL;
    snprintf(filename, 255, "tmp." __FILE__ "_%.2f.h264", factor);
    ffmpeg_encoder_start(filename, AV_CODEC_ID_H264, 25, width, height, factor);
    for (pts = 0; pts < 100; pts++) {
        frame->pts = pts;
        common_generate_rgb(width, height, pts, &rgb);
        ffmpeg_encoder_encode_frame(rgb);
    }
    ffmpeg_encoder_finish();
    free(rgb);
}

int main(int argc, char **argv) {
    int width = 320;
    int height = 240;
    if (argc > 1) {
        width = strtol(argv[1], NULL, 10);
        if (argc > 2) {
            height = strtol(argv[2], NULL, 10);
        }
    }
    encode_example(width, height, 0.5);
    encode_example(width, height, 1.0);
    encode_example(width, height, 2.0);
    return EXIT_SUCCESS;
}
