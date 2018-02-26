//
// Created by Akalanka on 24/02/2018.
//

#include "optimized_code.h"
#include <iostream>
#include "util.h"
#include "matrixOp.h"

#define NUMBER_OF_THREADS 3

using namespace std;

void calculate_time(int n, int size);
double optimized(int size,double **matrix1, double **matrix2, double **result_matrix);
void output_results(int size, double *values, const string &technique);

int main(){

    int sample_size, matrix_size, choice, exit;

    cout << "1 - Need to specify Matrix Size" << endl;
    cout << "2 - Do not need to specify Matrix Size" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter sample size: ";
        cin >> sample_size;
        cout << "Enter matrix length: ";
        cin >> matrix_size;
        calculate_time(matrix_size, sample_size);


    } else {
        cout << "Enter sample size: ";
        cin >> sample_size;
        for (int i = 1; i < 11; ++i) {
            calculate_time(i * 200, sample_size);
        }
    }
    cout << "Enter Q key to exit..";
    cin >> exit;
}

void calculate_time(int n, int size) {
    double **mat1 = initialize_matrix(n);
    double **mat2 = initialize_matrix(n);
    double **mat_res = initialize_matrix(n);

    double time_taken[size];

    cout << "matrix size: " << n << endl;

    for (int i = 0; i < size; i++) {
        populate_matrix(n, mat1);
        populate_matrix(n, mat2);
        time_taken[i] = optimized(n, mat1, mat2, mat_res);
    }

    output_results(size, time_taken, "optimized_method_1");

    delete_matrix(n, mat1);
    delete_matrix(n, mat2);
    delete_matrix(n, mat_res);
}

//Method to calculate the matrix multiplication
double optimized(int size,double **matrix1, double **matrix2, double **result_matrix){
    timer_start();
    //below line will take care of parallel execution of the for loop. this was provided by openmp
    //here we used openmp scheduling to speedup the code
    //reference https://github.com/Shafaet/OpenMP-Examples/blob/master/Parallel%20Matrix%20Multiplication.cpp
#pragma omp parallel for schedule(dynamic,NUMBER_OF_THREADS) shared(matrix1, matrix2, result_matrix)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result_matrix[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    timer_stop();
    return get_elapsed_time();
}

void output_results(int size, double *values, const string &technique) {
    double result[3];

    analyze_results(size, values, result);

    cout << technique << ": "
         << "[ average: " << result[0] << " s | "
         << "standard deviation: " << result[1] << " | "
         << "sample size required: " << result[2] << " ]"
         << endl;
}
