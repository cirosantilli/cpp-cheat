#!/usr/bin/env bash
set -eu
make O=3 ./bst_vs_heap.out
./bst_vs_heap.out > bst_vs_heap.dat
./bst_vs_heap.gnuplot
