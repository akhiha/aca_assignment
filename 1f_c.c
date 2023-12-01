#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>  // AVX intrinsics
#include <time.h>

double getElapsedTime(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
}

void initializeVectors(float *va, float *vb, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        va[i] = 1.0f + i;
        vb[i] = 2.0f + i;
    }
}

float dotProductEvenIndicesAVX(const float *vector1, const float *vector2, size_t length) {
    // ... [The rest of your dotProductEvenIndicesAVX function remains unchanged]
}

int main() {
    size_t length = 16;
    float *vector1 = (float*)aligned_alloc(32, length * sizeof(float));
    float *vector2 = (float*)aligned_alloc(32, length * sizeof(float));

    if (!vector1 || !vector2) {
        printf("Memory allocation failed\n");
        return 1;
    }

    struct timespec start, end;

    // Initialize vectors and measure time
    clock_gettime(CLOCK_MONOTONIC, &start);
    initializeVectors(vector1, vector2, length);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double initTime = getElapsedTime(start, end);

    // Compute dot product and measure time
    clock_gettime(CLOCK_MONOTONIC, &start);
    float result = dotProductEvenIndicesAVX(vector1, vector2, length);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double computeTime = getElapsedTime(start, end);

    printf("Dot Product of Even Indices: %f\n", result);
    printf("Initialization Time: %f seconds\n", initTime);
    printf("Computation Time: %f seconds\n", computeTime);

    free(vector1);
    free(vector2);

    // Determine if memory-bound or compute-bound
    if (computeTime > initTime) {
        printf("The program is compute-bound.\n");
    } else {
        printf("The program is memory-bound.\n");
    }

    return 0;
}
