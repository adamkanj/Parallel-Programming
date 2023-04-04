#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define COLUMS 600
#define INNER_DIM 650
#define ROWS 750

int main() {
    int (*matA)[COLUMS] =malloc(sizeof(int[ROWS][COLUMS]));
    int (*matB)[INNER_DIM] =malloc(sizeof(int[COLS][INNER_DIM]));
    int (*matC)[INNER_DIM] =malloc(sizeof(int[ROWS][INNER_DIM]));

    srand(time(NULL));
    for(int i =0;i< ROWS;i++) {
        for(int j = 0; j < COLUMS; j++) {
            matA[i][j] = rand() % 10;
        }
    }
    for(int i =0; i< COLUMS; i++) {
        for(int j= 0; j <INNER_DIM; j++) {
            matB[i][j] = rand() % 10;
        }
    }
    double Start_time = omp_get_wtime();
    #pragma omp parallel num_threads(4) {
        #pragma omp for
        for(int i = 0; i < ROWS; i++) {
            for(int j =0; j <INNER_DIM; j++) {
                int sum = 0;
                for(int k = 0;k< COLUMS; k++) {
                    sum += matA[i][k] * matB[k][j];
                }
                matC[i][j] = sum;
            }
        }
    }
    double End_time = omp_get_wtime();
    double elapsed_seconds = End_time - Start_time;
    printf(" Matrix multiplication IS successfully done in %f seconds.\n", elapsed_seconds);
    return 0;
}
