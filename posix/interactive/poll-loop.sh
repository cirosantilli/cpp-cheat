#!/usr/bin/env bash
set -x

# Infinite loop test.
# This is where poll shines: we manage to watch output from both pipes simultaneously,
# even though they both sleep for a long time! This is perfect for webservers.

sudo mknod poll0.tmp p
sudo mknod poll1.tmp p
sudo chmod 666 poll*.tmp
./poll.out &
i=0;
while true; do printf "$i"; i=$(($i+1)); sleep 1; done > poll0.tmp &
j=0;
while true; do printf "$j"; j=$(($j+1)); sleep 2; done > poll1.tmp &
sleep 8
kill %3
kill %2
kill %1
