#!/usr/bin/env gnuplot
set terminal png
set output "bst_vs_heap.png"
set multiplot layout 2,1
set title "Insert operation time"
set xlabel "size"
set ylabel "nanoseconds"
plot "bst_vs_heap.dat" using 2 title 'heap'
plot "bst_vs_heap.dat" using 3 title 'bst'
