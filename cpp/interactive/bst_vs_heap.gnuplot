#!/usr/bin/env gnuplot
set terminal png size 1024, 1024
set output "bst_vs_heap.png"
set multiplot layout 2,1 title "Heap vs BST insert time"
set xlabel "size"
set ylabel "nanoseconds"
set title "Heap"
plot "bst_vs_heap.dat" using 2 notitle
set title "BST"
plot "bst_vs_heap.dat" using 3 notitle
