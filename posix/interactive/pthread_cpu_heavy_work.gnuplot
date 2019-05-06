#!/usr/bin/env gnuplot
set terminal png size 1024, 1024
set style data linespoints
set output 'pthread_cpu_heavy_work.png'
set multiplot layout 3,1
set xlabel "threads"

set title "wall, user and sys"
set ylabel "time (s)"
set yrange [-20:]
set key right center
plot 'pthread_cpu_heavy_work.dat' using 1:2 title 'wall', \
     'pthread_cpu_heavy_work.dat' using 1:3 title 'user', \
     'pthread_cpu_heavy_work.dat' using 1:4 title 'sys'

set title "wall, user and sys / threads"
set yrange [0:]
set key right top
plot 'pthread_cpu_heavy_work.dat' using 1:($2/$1) title 'wall', \
     'pthread_cpu_heavy_work.dat' using 1:($3/$1) title 'user', \
     'pthread_cpu_heavy_work.dat' using 1:($4/$1) title 'sys'

set title 'user / wall ratio'
set ylabel "ratio"
set yrange [0:*]
plot 'pthread_cpu_heavy_work.dat' using 1:($3/$2) notitle
