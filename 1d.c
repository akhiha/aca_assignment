#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h> // AVX intrinsics
#include <time.h>

#define DATA_SIZE (1024 * 1024 * 1024) // 1 GB

double getElapsedTime(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
}

int main() {
    // Allocate memory
    float *data = (float*)aligned_alloc(32, DATA_SIZE * sizeof(float));
    if (!data) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize data
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        data[i] = (float)i;
    }

    // Read from the array using AVX
    __m256 sum = _mm256_setzero_ps();
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t i = 0; i < DATA_SIZE; i += 8) {
        __m256 val = _mm256_load_ps(&data[i]);
        sum = _mm256_add_ps(sum, val);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Prevent the compiler from optimizing out the loop
    volatile float preventOptimization = sum[0];

    double elapsedTime = getElapsedTime(start, end);
    double bandwidth = (DATA_SIZE * sizeof(float)) / elapsedTime / (1024 * 1024 * 1024); // GB/s

    printf("Elapsed Time: %f seconds\n", elapsedTime);
    printf("Memory Bandwidth (Read): %f GB/s\n", bandwidth);

    free(data);
    return 0;
}
