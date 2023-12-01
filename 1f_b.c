#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> // AVX intrinsics

// Function to get elapsed time in seconds
double getElapsedTime(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
}

// Function to initialize data
void initData(float *data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = (float)rand() / RAND_MAX;
    }
}

// Vectorized dot product function
float dotProductAVX(const float *vector1, const float *vector2, size_t length) {
    __m256 sum = _mm256_setzero_ps(); // Initialize sum to zero
    for (size_t i = 0; i < length; i += 8) {
        __m256 v1 = _mm256_loadu_ps(&vector1[i]);
        __m256 v2 = _mm256_loadu_ps(&vector2[i]);
        sum = _mm256_add_ps(sum, _mm256_mul_ps(v1, v2));
    }
    float result[8];
    _mm256_storeu_ps(result, sum);
    float dot = 0.0;
    for (int i = 0; i < 8; ++i) {
        dot += result[i];
    }
    return dot;
}

int main() {
    size_t size = 1000000; // Size of the vectors
    float *vector1 = (float*)aligned_alloc(32, size * sizeof(float));
    float *vector2 = (float*)aligned_alloc(32, size * sizeof(float));

    // Initialize data
    initData(vector1, size);
    initData(vector2, size);

    struct timespec startCompute, endCompute, startTotal, endTotal;

    // Measure total time including memory operations
    clock_gettime(CLOCK_MONOTONIC, &startTotal);
    // Measure only computation time
    clock_gettime(CLOCK_MONOTONIC, &startCompute);
    
    float result = dotProductAVX(vector1, vector2, size);

    clock_gettime(CLOCK_MONOTONIC, &endCompute);
    // Finish measuring total time
    clock_gettime(CLOCK_MONOTONIC, &endTotal);

    double computeTime = getElapsedTime(startCompute, endCompute);
    double totalTime = getElapsedTime(startTotal, endTotal);

    printf("Dot Product: %f\n", result);
    printf("Compute Time: %f seconds\n", computeTime);
    printf("Total Time (Including Memory Ops): %f seconds\n", totalTime);

    free(vector1);
    free(vector2);

    // Determine if memory-bound or compute-bound
    if (computeTime / totalTime > 0.5) {
        printf("The program is compute-bound.\n");
    } else {
        printf("The program is memory-bound.\n");
    }

    return 0;
}
