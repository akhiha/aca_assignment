#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // AVX2 intrinsics
#include <time.h>

#define NUM_ITERATIONS (100000000) // Number of iterations for the loop

double getElapsedTime(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
}

int main() {
    struct timespec start, end;
    __m256 a = _mm256_set1_ps(1.0f); // Set all elements to 1.0
    __m256 b = _mm256_set1_ps(2.0f); // Set all elements to 2.0

    // Start timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Perform a large number of floating point operations
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        a = _mm256_add_ps(a, b); // Each add operation is 8 floating point operations
    }

    // End timer
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate and print the GFLOPS
    double elapsedTime = getElapsedTime(start, end);
    double gflops = (NUM_ITERATIONS * 8.0) / elapsedTime / 1e9;
    printf("Peak Performance: %f GFLOPS\n", gflops);

    return 0;
}
