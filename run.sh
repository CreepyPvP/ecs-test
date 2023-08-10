#!/usr/bin/env bash
cd build
make
time ./ecs

# valgrind --tool=cachegrind --branch-sim=yes --mem-sim=yes build/ecs
