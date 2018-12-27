#!/usr/bin/env bash
for std in c++98 c++11 c++14 c++17 gnu++98 gnu++11 gnu++14 gnu++17; do
  echo $std
  g++ -std=$std -o cpp.out cpp.cpp
  ./cpp.out
  echo
done
echo default
g++ -o cpp.out cpp.cpp
./cpp.out
