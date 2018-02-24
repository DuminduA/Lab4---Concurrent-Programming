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
    int blockSize = 64;
    int ii,jj,kk,j,k;
#pragma omp parallel num_threads(NUMBER_OF_THREADS) shared(matrix1,matrix2,result_matrix,blockSize) private(ii,jj,kk,j,k)
    {
#pragma omp for schedule(static)

        for(int ii=0; ii<size; ii += blockSize){
            for(int jj=0; jj<size; jj += blockSize){
                for(int kk=0; kk<size; kk += blockSize){
                    for (int i = ii; i < min(ii+blockSize, size); ++i) {
                        for (int j = jj; j < min(jj+blockSize, size); ++j) {
                            for (int k = kk; k < min(kk+blockSize, size); k+=8) {
                                result_matrix[i][j] +=
                                        + matrix1[i][k]*matrix2[j][k]
                                        + matrix1[i][k+1]*matrix2[j][k+1]
                                        + matrix1[i][k+2]*matrix2[j][k+2]
                                        + matrix1[i][k+3]*matrix2[j][k+3]
                                        + matrix1[i][k+4]*matrix2[j][k+4]
                                        + matrix1[i][k+5]*matrix2[j][k+5]
                                        + matrix1[i][k+6]*matrix2[j][k+6]
                                        + matrix1[i][k+7]*matrix2[j][k+7];
                            }
                        }
                    }
                }
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
