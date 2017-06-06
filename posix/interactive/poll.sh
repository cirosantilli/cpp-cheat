#!/usr/bin/env bash
set -x
# Does not work with regular files.
# http://stackoverflow.com/questions/11901884/how-can-select-wait-on-regular-file-descriptors-non-sockets
sudo mknod poll0.tmp p
sudo mknod poll1.tmp p
sudo chmod 666 poll*.tmp

./poll.out &
printf a > poll0.tmp
printf b > poll1.tmp
kill %1
# => loop
# => POLLIN i=0 n=1 buf=a
# => loop
# => POLLHUP i=0
# => loop
# => POLLIN i=1 n=1 buf=b
# => POLLHUP i=1
# => loop
