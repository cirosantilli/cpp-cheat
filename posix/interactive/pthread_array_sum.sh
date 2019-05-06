#!/usr/bin/env bash
set -eu
make -B O=3 pthread_array_sum.out
./pthread_array_sum.out 1000000000 | tee pthread_array_sum.dat
./pthread_array_sum.gnuplot
