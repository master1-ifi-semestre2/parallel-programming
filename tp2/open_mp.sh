#!/bin/sh

# Je compile
#my_gcc -Wall --std=c99 -o $1 $2 -fopenmp

/usr/local/Cellar/gcc/7.3.0/bin/gcc-7 -Wall --std=c99 -o $1 $2 -fopenmp
