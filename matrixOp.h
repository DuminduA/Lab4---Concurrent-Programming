//
// Created by Akalanka on 23/02/2018.
//

#ifndef LAB4_140019E_140_MATRIXOP_H
#define LAB4_140019E_140_MATRIXOP_H

double **initialize_matrix(int n);

void populate_matrix(int n, double **mat);

void delete_matrix(int n, double **mat);

double **transpose(double **matrix,double **transposed, int size);

void reduce_to_One_dimention(int n, double *reduced_matrix, double **matrix);

double *oneDimention_matrix(int n);


#endif //LAB4_140019E_140_MATRIXOP_H
