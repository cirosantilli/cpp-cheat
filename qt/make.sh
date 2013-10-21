#!/usr/bin/env bash

set -e

if [ ! -r qt.pro ]; then
    qmake -project
fi
qmake
make
./qt
