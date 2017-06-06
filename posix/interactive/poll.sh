#!/usr/bin/env bash
set -x
# Does not work with regular files.
# http://stackoverflow.com/questions/11901884/how-can-select-wait-on-regular-file-descriptors-non-sockets
sudo mknod poll0.tmp p
sudo mknod poll1.tmp p
sudo chmod 666 poll*.tmp

# Simple test.
./poll.out &
printf a > poll0.tmp
printf b > poll1.tmp
kill %1
# => loop
# => i=0 n=1 buf=a
# => loop
# => loop
# => i=1 n=1 buf=b
# => loop

# Infinite loop test.
# This is where poll shines: we manage to watch output from both pipes simultaneously,
# even though they both sleep for a long time! This is perfect for webservers.
./poll.out &
i=0;
while true; do printf "$i"; i=$(($i+1)); sleep 1; done > poll0.tmp &
j=0;
while true; do printf "$j"; j=$(($j+1)); sleep 2; done > poll1.tmp &
sleep 8
kill %3
kill %2
kill %1
