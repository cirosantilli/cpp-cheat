/*
http://stackoverflow.com/a/36510894/895245

TODO

- smooth transition between sines without tic sound. Needs a phase change I imagine.
- ADSR https://en.wikipedia.org/wiki/Synthesizer#Attack_Decay_Sustain_Release_.28ADSR.29_envelope
    Currently, hitting the same not twice sounds the same as hitting it once for double the time,
    (except for the tic of phase, which is a bug as well...)
- drum / percurssion synth
*/

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint16_t point_type;

#define WRITE(name, func) \
    f = fopen("tmp." name ".raw", "wb"); \
    for (t = 0; t < NSAMPLES; ++t) { \
        func; \
        write_ampl(f, ampl); \
    } \
    fclose(f);

double PI2;

void write_ampl(FILE *f, point_type ampl) {
    uint8_t bytes[2];
    bytes[0] = ampl >> 8;
    bytes[1] = ampl & 8;
    fwrite(bytes, 2, sizeof(uint8_t), f);
}

/* https://en.wikipedia.org/wiki/Piano_key_frequencies */
double piano_freq(unsigned int i) {
    return 440.0 * pow(2, (i - 49.0) / 12.0);
}

/* Chord formed by the nth note of the piano. */
point_type piano_sum(unsigned int max_ampl, unsigned int time,
        double sample_freq, unsigned int nargs, unsigned int *notes) {
    double freq;
    unsigned int i;
    double sum = 0;
    for (i = 0 ; i < nargs; ++i)
        sum += sin(PI2 * time * piano_freq(notes[i]) / sample_freq);
    return max_ampl * 0.5 * (nargs + sum) / nargs;
}

enum notes {
    A0 = 1, AS0, B0,
    C1, C1S, D1, D1S, E1, F1, F1S, G1, G1S, A1, A1S, B1,
    C2, C2S, D2, D2S, E2, F2, F2S, G2, G2S, A2, A2S, B2,
    C3, C3S, D3, D3S, E3, F3, F3S, G3, G3S, A3, A3S, B3,
    C4, C4S, D4, D4S, E4, F4, F4S, G4, G4S, A4, A4S, B4,
    C5, C5S, D5, D5S, E5, F5, F5S, G5, G5S, A5, A5S, B5,
    C6, C6S, D6, D6S, E6, F6, F6S, G6, G6S, A6, A6S, B6,
    C7, C7S, D7, D7S, E7, F7, F7S, G7, G7S, A7, A7S, B7,
    C8,
};

int main(void) {
    FILE *f;
    PI2 = 2 * acos(-1.0);
    const double SAMPLE_FREQ = 44100;
    const unsigned int NSAMPLES = 4 * SAMPLE_FREQ;
    double freq;
    point_type ampl;
    point_type max_ampl = UINT16_MAX;
    unsigned int t;

    WRITE("1000", (ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 1000.0 / SAMPLE_FREQ))));

    /* Maximum and minimum of human audition. TODO explain their weird sound. */
    WRITE("20", (ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 20.0 / SAMPLE_FREQ))));
    WRITE("2000", (ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 2000.0 / SAMPLE_FREQ))));

    /* Out of human range. TODO explain outcome. */
    WRITE("10", (ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 10.0 / SAMPLE_FREQ))));
    WRITE("40000", (ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 40000.0 / SAMPLE_FREQ))));

    /* Smaller amplitude: less loud. */
    WRITE("half", (ampl = max_ampl * 0.25 * (1.0 + sin(PI2 * t * 1000.0 / SAMPLE_FREQ))));

    /* Constant amplitude: produces only 2 quick ticks at start and end,
     * when the speaker's membrane moves. */
    WRITE("const", (ampl = max_ampl));

    /* TODO: why does this produces only two ticks, and not a bunch of ticks? */
    f = fopen("tmp.max_min.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        if (t % 2 == 0) {
            ampl = 0;
        } else {
            ampl = max_ampl;
        }
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    Dual channel, one sin per channel.
    Play with ffmpeg -ac 2.
    Get microphones. Each phone gives a different frequency.
    */
    f = fopen("tmp.dual.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 100.0 / SAMPLE_FREQ));
        write_ampl(f, ampl);
        ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * 2000.0 / SAMPLE_FREQ));
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    Sum of sinuses with different frequencies and same amplitude.
    AKA chord.
    */
    f = fopen("tmp.sum.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = max_ampl * 0.25 * (
            2.0 +
            sin(PI2 * t * 1000.0 / SAMPLE_FREQ) +
            sin(PI2 * t * 2000.0 / SAMPLE_FREQ)
        );
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    Sum of sinuses with different frequencies, and different amplitudes.
    */
    f = fopen("tmp.sum_ampl.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = max_ampl * (1.0 / 12.0) * (
            6.0 +
            sin(PI2 * t * 1000.0 / SAMPLE_FREQ) * 5.0 +
            sin(PI2 * t * 2000.0 / SAMPLE_FREQ)
        );
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    See how a phase shift sounds like. No difference?
    But obviously in some cases there must be a difference, e.g. canceling waves.
    http://www.silcom.com/~aludwig/Phase_audibility.htm
    */
    f = fopen("tmp.sum_phase.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = max_ampl * 0.25 * (
            2.0 +
            sin(PI2 * t *  500.0 / SAMPLE_FREQ) +
            sin((PI2 * t * 2000.0 / SAMPLE_FREQ) + (PI2 / 4.0))
        );
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    https://en.wikipedia.org/wiki/Chirp
    Linearly varying instanteneous frequency.
    http://math.stackexchange.com/questions/85388/does-the-phrase-instantaneous-frequency-make-sense
    TODO understand intuitively why if we remove the 2.0 divisor from the frequency
    then it goes first up and then down.
    Yes, I know that mathematically it comes from the derivative.
    */
    f = fopen("tmp.chirp.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        freq = 20.0 + 19980.0 * t / ((double)NSAMPLES * 2.0);
        ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * freq / SAMPLE_FREQ));
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    Saw tooth
    https://www.youtube.com/watch?v=uIuJTWS2uvY mentions that high frequency saws
    and sines are more similar than low frequency. This is because
    humans don't hear the higher harmonics, and the lower one dominates.
    */
    f = fopen("tmp.saw.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        freq = 1000;
        ampl = max_ampl * fabs(1.0 - 2.0 * (t % (int)(SAMPLE_FREQ / freq)) / (SAMPLE_FREQ / freq));
        write_ampl(f, ampl);
    }
    fclose(f);

    f = fopen("tmp.tune.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        if (t < NSAMPLES / 4) {
            freq = piano_freq(C4);
        } else if (t < NSAMPLES / 2) {
            freq = piano_freq(E4);
        } else if (t < 3 * NSAMPLES / 4) {
            freq = piano_freq(G4);
        } else {
            freq = piano_freq(C5);
        }
        ampl = max_ampl * 0.5 * (1.0 + sin(PI2 * t * freq / SAMPLE_FREQ));
        write_ampl(f, ampl);
    }
    fclose(f);

    f = fopen("tmp.chord.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = piano_sum(max_ampl, t, SAMPLE_FREQ, 4, (unsigned int[]){C4, E4, G4, B4});
        write_ampl(f, ampl);
    }
    fclose(f);

    /*
    # Pianola

    # Canon

        https://en.wikipedia.org/wiki/Player_piano

        http://www.8notes.com/scores/420.asp After where I've stopped,
        that score gets weird, maybe find another one.
    */
    {
        unsigned int i;
        unsigned int samples_per_unit = SAMPLE_FREQ * 0.375;
        unsigned int *ip[] = {
            (unsigned int[]){4, 2, C3, E4},
            (unsigned int[]){4, 2, G3, D4},
            (unsigned int[]){4, 2, A3, C4},
            (unsigned int[]){4, 2, E3, B3},

            (unsigned int[]){4, 2, F3, A3},
            (unsigned int[]){4, 2, C3, G3},
            (unsigned int[]){4, 2, F3, A3},
            (unsigned int[]){4, 2, G3, B3},

            (unsigned int[]){4, 3, C3, G4, E5},
            (unsigned int[]){4, 3, G3, B4, D5},
            (unsigned int[]){4, 2, A3,     C5},
            (unsigned int[]){4, 3, E3, G4, B4},

            (unsigned int[]){4, 3, F3, C4, A4},
            (unsigned int[]){4, 3, C3, G4, G4},
            (unsigned int[]){4, 3, F3, F4, A4},
            (unsigned int[]){4, 3, G3, D4, B4},

            (unsigned int[]){2, 3, C4, E4, C5},
            (unsigned int[]){2, 3, C4, E4, C5},
            (unsigned int[]){2, 3, G3, D4, D5},
            (unsigned int[]){2, 3, G3, D4, B4},

            (unsigned int[]){2, 3, A3, C4, C5},
            (unsigned int[]){2, 3, A3, C4, E5},
            (unsigned int[]){2, 2, E3,     G5},
            (unsigned int[]){2, 2, E3,     G4},

            (unsigned int[]){2, 3, F3, A3, A4},
            (unsigned int[]){2, 3, F3, A3, F4},
            (unsigned int[]){2, 3, C3,     E4},
            (unsigned int[]){2, 3, C3,     G4},

            (unsigned int[]){2, 3, F3, A3, F4},
            (unsigned int[]){2, 3, F3, A3, C5},
            (unsigned int[]){2, 3, G3, B3, B4},
            (unsigned int[]){2, 3, G3, B3, G4},

            (unsigned int[]){2, 3, C4, E4, C5},
            (unsigned int[]){1, 3, C4, E4, E5},
            (unsigned int[]){1, 3, C4, E4, G5},
            (unsigned int[]){1, 2, G3,     G5},
            (unsigned int[]){1, 2, G3,     A5},
            (unsigned int[]){1, 2, G3,     G5},
            (unsigned int[]){1, 2, G3,     F5},

            (unsigned int[]){3, 3, A3, C4, E5},
            (unsigned int[]){1, 3, A3, C4, E5},
            (unsigned int[]){1, 3, E3, G3, E5},
            (unsigned int[]){1, 3, E3, G3, F5},
            (unsigned int[]){1, 3, E3, G3, E5},
            (unsigned int[]){1, 3, E3, G3, D5},
        };
        f = fopen("tmp.canon.raw", "wb");
        for (i = 0; i < sizeof(ip) / sizeof(int*); ++i) {
            unsigned int *cur = ip[i];
            unsigned int total = samples_per_unit * cur[0];
            for (t = 0; t < total; ++t) {
                ampl = piano_sum(max_ampl, t, SAMPLE_FREQ, cur[1], &cur[2]);
                write_ampl(f, ampl);
            }
        }
        fclose(f);
    }

    return EXIT_SUCCESS;
}
