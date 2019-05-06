#!/usr/bin/env bash
i=1
n="$(($(nproc) * 2))"
rm -f pthread_cpu_heavy_work.dat
while [ "$i" -le "$n" ]; do
  env time \
    --append \
    --format "$i %e %U %S" \
    --output pthread_cpu_heavy_work.dat \
    ./pthread_cpu_heavy_work.out 10000000000 "$i" \
  ;
  i=$((i + 1))
done
./pthread_cpu_heavy_work.gnuplot
