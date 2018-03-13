#!/bin/sh
clang-omp -o $2 -Wall --std=c99 $1 -fopenmp