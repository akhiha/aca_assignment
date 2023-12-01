#include <stdio.h>
#include <stdlib.h>

#define N 2048           // Matrix size
#define TILE_SIZE 64     // Tile size - this needs to be optimized

// Function to allocate a matrix
int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to initialize a matrix with random values
void initializeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;  // Random values between 0 and 99
        }
    }
}

// Function to free a matrix
void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Tiled matrix multiplication function
void multiplyMatricesTiled(int **a, int **b, int **c, int n) {
    for (int i = 0; i < n; i += TILE_SIZE) {
        for (int j = 0; j < n; j += TILE_SIZE) {
            for (int k = 0; k < n; k += TILE_SIZE) {
                for (int i0 = i; i0 < i + TILE_SIZE; ++i0) {
                    for (int j0 = j; j0 < j + TILE_SIZE; ++j0) {
                        for (int k0 = k; k0 < k + TILE_SIZE; ++k0) {
                            c[i0][j0] += a[i0][k0] * b[k0][j0];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int **A = allocateMatrix(N);
    int **B = allocateMatrix(N);
    int **C = allocateMatrix(N);

    initializeMatrix(A, N);
    initializeMatrix(B, N);

    multiplyMatricesTiled(A, B, C, N);

    // For debugging: print a small part of matrix C
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(C, N);

    return 0;
}
