#!/usr/bin/bash

cmake -B build -S . \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -G Ninja

cmake --build build -j12
