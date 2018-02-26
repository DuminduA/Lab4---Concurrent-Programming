//
// Created by Akalanka on 25/02/2018.
//

#include "optimized_code_2.h"
//
// Created by Akalanka on 24/02/2018.
//

#include "optimized_code.h"
#include <iostream>
#include "util.h"
#include "matrixOp.h"

#define NUMBER_OF_THREADS 2

using namespace std;

void calculate_time(int n, int size);
double optimized_method_2(int size,double **matrix1, double **matrix2, double **result_matrix);
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
    double **mat_res = initialize_matrix(n);

    double time_taken[size];

    cout << "matrix size: " << n << endl;

    for (int i = 0; i < size; i++) {
        populate_matrix(n, mat1);
        populate_matrix(n, mat2);
        populate_matrix(n,transpose_mat2);
        transpose(mat2, transpose_mat2, n);
        time_taken[i] = optimized_method_2(n, mat1, transpose_mat2, mat_res);
    }

    output_results(size, time_taken, "optimized_method_2");

    delete_matrix(n, mat1);
    delete_matrix(n, mat2);
    delete_matrix(n, mat_res);
}

//Method to calculate the matrix multiplication
double optimized_method_2(int size,double **matrix1, double **matrix2, double **result_matrix){
    timer_start();
    //below line will take care of parallel execution of the for loop. this was provided by openmp
    //refernce https://blogs.msdn.microsoft.com/xiangfan/2009/04/28/optimize-your-code-matrix-multiplication/
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result_matrix[i][j] += matrix1[j][i] * matrix2[j][i];

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
