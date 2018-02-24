//
// Created by Akalanka on 23/02/2018.
//

#include "omp.h"
#include "util.h"
#include "math.h"

double start_time, end_time;

void timer_start() {
    start_time = omp_get_wtime();
}

void timer_stop() {
    end_time = omp_get_wtime();
}

double get_elapsed_time() {
    return end_time - start_time;
}

double calculate_average(int size, double values[]){
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += values[i];
    }
    double ave = sum / size;

    return ave;
}

double calculate_std_deviation(int size, double values[], double ave){
    double squared_sum = 0;
    for (int i = 0; i < size; i++) {
        squared_sum += pow(values[i], 2);
    }

    double sd = sqrt(squared_sum / size - pow(ave, 2));
    return sd;
}

void analyze_results(int size,double *values,double *result){
    result[0] = calculate_average(size, values);
    result[1] = calculate_std_deviation(size, values, result[0]);

    double Z = 1.960;
    double R = 5;

    double s_size = ceil(pow((100 * Z * result[1]) / (R * result[0]), 2));

    result[2] = s_size;
}
