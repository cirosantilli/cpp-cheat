Backup for: https://stackoverflow.com/questions/2205070/how-to-programmatically-synthesize-music/52126471#52126471 in case they delete the question. Title: "How to programmatically synthesize music?"

**Canon in D in C**

Outcome: https://www.youtube.com/watch?v=JISozfHATms

main.c:

    #include <math.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>

    typedef uint16_t point_type_t;

    double PI2;

    void write_ampl(FILE *f, point_type_t ampl) {
        uint8_t bytes[2];
        bytes[0] = ampl >> 8;
        bytes[1] = ampl & 0xFF;
        fwrite(bytes, 2, sizeof(uint8_t), f);
    }

    /* https://en.wikipedia.org/wiki/Piano_key_frequencies */
    double piano_freq(unsigned int i) {
        return 440.0 * pow(2, (i - 49.0) / 12.0);
    }

    /* Chord formed by the nth note of the piano. */
    point_type_t piano_sum(unsigned int max_ampl, unsigned int time,
            double sample_freq, unsigned int nargs, unsigned int *notes) {
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
        point_type_t ampl;
        point_type_t max_ampl = UINT16_MAX;
        unsigned int t, i;
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
        f = fopen("canon.raw", "wb");
        for (i = 0; i < sizeof(ip) / sizeof(int*); ++i) {
            unsigned int *cur = ip[i];
            unsigned int total = samples_per_unit * cur[0];
            for (t = 0; t < total; ++t) {
                ampl = piano_sum(max_ampl, t, SAMPLE_FREQ, cur[1], &cur[2]);
                write_ampl(f, ampl);
            }
        }
        fclose(f);
        return EXIT_SUCCESS;
    }

Generate `canon.raw`:

    gcc -std=c99 -o main main.c -lm
    ./main

Play `canon.raw` directly:

    sudo apt-get install ffmpeg
    ffplay -autoexit -f u16be -ar 44100 -ac 1 canon.raw

or convert to a more common audio format and then play with a more common audio player:

    ffmpeg -f u16be -ar 44100 -ac 1 -i canon.raw canon.flac
    vlc canon.flac

or convert into a video for YouTube:

    wget -O canon.png https://upload.wikimedia.org/wikipedia/commons/thumb/3/35/The_C_Programming_Language_logo.svg/564px-The_C_Programming_Language_logo.svg.png
    ffmpeg -loop 1 -y -i canon.png -i canon.flac -shortest -acodec copy -vcodec vp9 canon.mkv

as explained: https://superuser.com/questions/1041816/combine-one-image-one-audio-file-to-make-one-video-using-ffmpeg/1041818#1041818

Here is a more physics oriented view of audio generation: https://stackoverflow.com/questions/732699/how-is-audio-represented-with-numbers/36510894#36510894

Tested on Ubuntu 18.04. [GitHub upstream](https://github.com/cirosantilli/cpp-cheat/blob/d046111efbd6353bd5d8df16733472baab2ffc52/c/interactive/audio_gen.c#L214).
