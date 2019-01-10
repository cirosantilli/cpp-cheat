#!/usr/bin/env bash
set -eux
cflags='-ggdb3 -std=c99 -O0 -fPIE -pie'
gcc $cflags -c -o f1.o f1.c
gcc $cflags -c -o f2.o f2.c
gcc $cflags -c -o f12.o f12.c
ld -o f12_r.o f1.o f2.o
gcc $cflags -c -o main.o main.c
gcc $cflags -o main.out f12.o main.o
gcc $cflags -o main_r.out f12_r.o main.o
./main.out
./main_r.out
