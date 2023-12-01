#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

float dotProductOfVectors(const float *va, const float *vb, int size) {
    float result = 0.0f;
    for (int i = 0; i < size; ++i) {
        result += va[i] * vb[i];
    }
    return result;
}

void initializeVectors(float *va, float *vb, int size) {
    for (int i = 0; i < size; ++i) {
        va[i] = 1.0 + (i % 3);
        vb[i] = 1.0 + (i % 4);
    }
}

int main() {
    int size = 48;
    float *vector_a = malloc(size * sizeof(float));
    float *vector_b = malloc(size * sizeof(float));

    // Measure initialization time
    double start_init_time = omp_get_wtime();
    initializeVectors(vector_a, vector_b, size);
    double end_init_time = omp_get_wtime();
    double init_time = end_init_time - start_init_time;

    // Measure computation time
    double start_compute_time = omp_get_wtime();
    float result = dotProductOfVectors(vector_a, vector_b, size);
    double end_compute_time = omp_get_wtime();
    double compute_time = end_compute_time - start_compute_time;

    printf("Scalar Dot Product: %.2f\n", result);
    printf("Initialization Time: %.6f seconds\n", init_time);
    printf("Computation Time: %.6f seconds\n", compute_time);

    free(vector_a);
    free(vector_b);

    // Determine if memory-bound or compute-bound
    if (compute_time > init_time) {
        printf("The program is compute-bound.\n");
    } else {
        printf("The program is memory-bound.\n");
    }

    return 0;
}
