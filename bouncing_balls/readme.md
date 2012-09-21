Simple homework for my university, therefore simple implementation (not that I know how to do *that much* better now =) )

Homework requirements found in requirements.pdf.

To compile and run use:

    DIR_IN_PATH=~/bin
    OUT="$DIR_IN_PATH"/glutcomprun
    wget -nc -O "$OUT" https://raw.github.com/cirosantilli/bash/ae0473cc9c29f98dfc0f02224c1f2b0b03b4b3f2/glutcomprun && \
    chmod +x "$OUT"

    glutcomprun one_ball.cpp 1

    glutcomprun multi_ball.cpp 1
