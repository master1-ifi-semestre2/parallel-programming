#!/bin/sh

#clang-omp -Wall --std=c99 -o $1 $2 -fopenmp
clang-omp -o $2 -Wall --std=c99 $1 -fopenmp