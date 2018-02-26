//
// Created by Akalanka on 23/02/2018.
//
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "time.h"
#include "matrixOp.h"

//initializing the matrix to be created
double **initialize_matrix(int size){
    auto **matrix = new double *[size];

    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
    }

    return matrix;
}

//populate random values to the matrix
void populate_matrix(int size, double **matrix){
//    srand((unsigned int) 100 * (time(0)));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (rand() % 90) + 10;
        }
    }
}

//delete the matrix after use
void delete_matrix(int n, double **mat) {
    for (int i = 0; i < n; i++) {
        delete[] mat[i];
    }

    delete[] mat;
}

double **transpose(double **matrix,double **transposed, int size) {
    // Finding transpose of matrix[][] and storing it in transposed[][]
    int i,j;
#pragma omp parallel shared(matrix,transposed) private(i,j)
    {
#pragma omp for schedule(static)
        for(i = 0; i < size; ++i){
            for(j = 0; j < size; ++j){
                transposed[j][i]=matrix[i][j];
            }
        }
    }
    return transposed;
}

void reduce_to_One_dimention(int n, double *reduced_matrix, double **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            reduced_matrix[i * n + j] = matrix[i][j];
        }
    }
}

double *oneDimention_matrix(int n) {
    auto *mat = new double[n * n];
    return mat;
}
