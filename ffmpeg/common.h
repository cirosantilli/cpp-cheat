#ifndef COMMON_H
#define COMMON_H

#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>

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
void common_generate_rgb(int width, int height, int pts, uint8_t **rgbp) {
    int x, y, cur;
    uint8_t *rgb = *rgbp;
    rgb = realloc(rgb, 3 * sizeof(uint8_t) * height * width);
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            cur = 3 * (y * width + x);
            rgb[cur + 0] = 0;
            rgb[cur + 1] = 0;
            rgb[cur + 2] = 0;
            if ((pts / 25) % 2 == 0) {
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

#endif
