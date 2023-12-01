#!/bin/bash

for l1_size in {1024,2048,4096,8192}; do
    for l2_size in {8192,16384,32768,65536}; do
        valgrind --tool=cachegrind --I1=$l1_size,1,64 --D1=$l1_size,1,64 --LL=$l2_size,1,64 ./3_cache
        cg_annotate cachegrind.out.xxxx > results_${l1_size}_${l2_size}.txt
    done
done
