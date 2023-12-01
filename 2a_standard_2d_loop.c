#include <stdio.h>
#include <stdlib.h>

#define N 10 // Matrix size (N x N)

void standardMatrixMultiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Helper function to print the matrix
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void initializeMatrix(int matrix[N][N]) {
    int num = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = num++;
        }
    }
}

int main() {

    int A[N][N], B[N][N], C[N][N];

    initializeMatrix(A);
    initializeMatrix(B);

    standardMatrixMultiply(A, B, C);

    printf("Matrix A:\n");
    printMatrix(A);
    printf("\nMatrix B:\n");
    printMatrix(B);
    printf("\nMatrix C (Product):\n");
    printMatrix(C);

    return 0;
}
