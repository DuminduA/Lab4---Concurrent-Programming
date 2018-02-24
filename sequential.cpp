//
// Created by Akalanka on 23/02/2018.
//
#include <iostream>
#include "util.h"
#include "matrixOp.h"

using namespace std;

void calculate_time(int n, int size);
double run_sequencially(int size,double **matrix1, double **matrix2, double **result_matrix);
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
        time_taken[i] = run_sequencially(n, mat1, mat2, mat_res);

        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cout<< mat1[j][k];
                cout << " ";
            }
            cout << "\n";
        }
        cout<<"\n";
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cout<< mat2[j][k];
                cout << " ";
            }
            cout << "\n";
        }
        cout<<"\n";
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cout<< mat_res[j][k];
                cout << " ";
            }
            cout << "\n";
        }
    }


    output_results(size, time_taken, "sequential");

    delete_matrix(n, mat1);
    delete_matrix(n, mat2);
    delete_matrix(n, mat_res);
}

//Method to calculate the matrix multiplication
double run_sequencially(int size,double **matrix1, double **matrix2, double **result_matrix){
    timer_start();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result_matrix[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result_matrix[i][j] += matrix1[i][k] * matrix2[k][i];
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
