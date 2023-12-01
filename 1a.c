#include <stdio.h>
#include <omp.h>

float dotProductOfVectors(const float * const vector1, const float * const vector2, size_t length) {
    float result = 0.0f;
    #pragma omp parallel for reduction(+:result)
    for (size_t i = 0; i < length; ++i) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

int main() {
    float vector_1[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5, 30.5, 31.5, 32.5, 33.5, 34.5, 35.5, 36.5, 37.5, 38.5, 39.5, 40.5};
    float vector_2[] = {41.5, 42.5, 43.5, 44.5, 45.5, 46.5, 47.5, 48.5, 49.5, 50.5, 51.5, 52.5, 53.5, 54.5, 55.5, 56.5, 57.5, 58.5, 59.5, 60.5, 61.5, 62.5, 63.5, 64.5, 65.5, 66.5, 67.5, 68.5, 69.5, 70.5, 71.5, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5, 78.5, 79.5, 80.5};

    size_t length = sizeof(vector_1) / sizeof(vector_1[0]);

    double start_time = omp_get_wtime();
    float result = dotProductOfVectors(vector_1, vector_2, length);

    double end_time = omp_get_wtime();
    double actual_time = end_time - start_time;

    printf("Scalar Dot Product: %.2f\n", result);
    printf("Time for Scalar Dot Product: %.6f seconds\n", actual_time);

    return 0;
}
