#include <stdio.h>
#include <immintrin.h>  // AVX intrinsics
#include <omp.h>

float dotProductEvenIndicesAVX(const float *vector1, const float *vector2, size_t length) {
    __m256 sum = _mm256_setzero_ps();  // Initialize sum to zero

    for (size_t i = 0; i < length; i += 16) {  // Process 16 elements per iteration
        // Load 16 contiguous values from each vector, but we'll use only half of them
        __m256 v1a = _mm256_loadu_ps(&vector1[i]);
        __m256 v1b = _mm256_loadu_ps(&vector1[i + 8]);
        __m256 v2a = _mm256_loadu_ps(&vector2[i]);
        __m256 v2b = _mm256_loadu_ps(&vector2[i + 8]);

        // Shuffle vectors to keep only even-indexed elements
        __m256 v1_even = _mm256_shuffle_ps(v1a, v1b, _MM_SHUFFLE(2, 0, 2, 0));
        __m256 v2_even = _mm256_shuffle_ps(v2a, v2b, _MM_SHUFFLE(2, 0, 2, 0));

        // Multiply the values and add to the sum
        sum = _mm256_add_ps(sum, _mm256_mul_ps(v1_even, v2_even));
    }

    // Perform horizontal addition
    __m256 hsum = _mm256_hadd_ps(sum, sum);
    hsum = _mm256_hadd_ps(hsum, hsum);

    // Extract and add the sums
    __m128 low = _mm256_castps256_ps128(hsum);
    __m128 high = _mm256_extractf128_ps(hsum, 1);
    low = _mm_add_ps(low, high);

    float result[4];
    _mm_storeu_ps(result, low);
    return result[0] + result[1];
}

int main() {
    float vector_1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
    float vector_2[] = {16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    size_t length = sizeof(vector_1) / sizeof(vector_1[0]);

    double startTimeVector = omp_get_wtime();

    float result = dotProductEvenIndicesAVX(vector_1, vector_2, length);

    double endTimeVector = omp_get_wtime();
    double elapsedTimeVector = endTimeVector - startTimeVector;


    printf("Dot Product of Even Indices: %f\n", result);
    printf("Time for Vectorized Dot Product: %.6f seconds\n", elapsedTimeVector);


    return 0;
}
