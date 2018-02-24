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

    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
    }

    return matrix;
}

//populate random values to the matrix
void populate_matrix(int size, double **matrix){
    srand((unsigned int) (time(nullptr)));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (rand() % 100) + 1;
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
