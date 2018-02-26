//
// Created by Akalanka on 25/02/2018.
//

#include "optimized_method_3.h"
#include <iostream>
#include "util.h"
#include "matrixOp.h"

#define BLOCK_SIZE 8


using namespace std;

void calculate_time(int n, int size);
double optimized_method_3(int size,double *matrix1, double *matrix2, double *result_matrix);
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
    double **transpose_mat2 = initialize_matrix(n);
    double *mat1_OneDim = oneDimention_matrix(n);
    double *mat2_OneDim = oneDimention_matrix(n);
    double *mat_result = oneDimention_matrix(n);

    double time_taken[size];

    cout << "matrix size: " << n << endl;

    for (int i = 0; i < size; i++) {
        populate_matrix(n, mat1);
        populate_matrix(n, mat2);
        transpose(mat2,transpose_mat2,n);
        reduce_to_One_dimention(n,mat1_OneDim,mat1);
        reduce_to_One_dimention(n,mat2_OneDim,transpose_mat2);
        time_taken[i] = optimized_method_3(n, mat1_OneDim, mat2_OneDim, mat_result);
    }

    output_results(size, time_taken, "optimized_method_3");

    delete_matrix(n, mat1);
    delete_matrix(n, mat2);
}

//Method to calculate the matrix multiplication
double optimized_method_3(int n,double *mat1_OneDim, double *mat2_OneDim, double *mat_result){
    int block_size_mat1, block_size_mat2;
    double sum;
    timer_start();
    //below line will take care of parallel execution of the for loop. this was provided by openmp

#pragma omp parallel for shared(mat1_OneDim, mat2_OneDim, mat_result) private(block_size_mat1, block_size_mat2, sum)
    for (int i = 0; i < n; i++) {
        block_size_mat1 = i * n; // this is calculating only once
        for (int j = 0; j < n; j++) {
            block_size_mat2 = j * n; // this is calculating only once
            sum = 0; // using this local variable reduce the memory usage and refernces to result matrix
            for (int k = 0; k < min(n,(k+1)*BLOCK_SIZE); k += BLOCK_SIZE) {
                sum += mat1_OneDim[block_size_mat1 + k] * mat2_OneDim[block_size_mat2 + k] +
                        mat1_OneDim[block_size_mat1 + k + 1] * mat2_OneDim[block_size_mat2 + k + 1] +
                        mat1_OneDim[block_size_mat1 + k + 2] * mat2_OneDim[block_size_mat2 + k + 2] +
                        mat1_OneDim[block_size_mat1 + k + 3] * mat2_OneDim[block_size_mat2 + k + 3] +
                        mat1_OneDim[block_size_mat1 + k + 4] * mat2_OneDim[block_size_mat2 + k + 4] +
                        mat1_OneDim[block_size_mat1 + k + 5] * mat2_OneDim[block_size_mat2 + k + 5] +
                        mat1_OneDim[block_size_mat1 + k + 6] * mat2_OneDim[block_size_mat2 + k + 6] +
                        mat1_OneDim[block_size_mat1 + k + 7] * mat2_OneDim[block_size_mat2 + k + 7];
            }
            mat_result[block_size_mat1 + j] = sum; // access result matrix only once
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
