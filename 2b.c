#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int** allocateMatrix(int n) {
    int** matrix = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;  // Populate with random values
        }
    }
    return matrix;
}

void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    for (int k = 4; k <= 10; k++) {
        int n = 1 << k;  // Compute 2^k
        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        multiplyMatrices(A, B, C, n);

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);

        printf("Completed %dx%d matrix multiplication\n", n, n);
    }

    return 0;
}
