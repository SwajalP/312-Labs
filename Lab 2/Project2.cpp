// matrix-multiplication <Project2.cpp>
// ECE 312 Project 2 submission by
// Swajal Padhi
// skp2628
// Slip days used: <0>
// Spring 2025

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],  
        const uint32_t b_cols,   
        double c[]) {
        if(a_rows == 0 ||  a_cols == 0|| b_cols == 0)
            return;
        for(int rowA  = 0; rowA < a_rows; rowA++){
            for(int colB = 0; colB < b_cols; colB++){
                double sum = 0.0;
                for(int colA = 0; colA < a_cols; colA++){
                    sum += a[rowA * a_cols + colA ] * b[colA * b_cols + colB];  
                }
                c[rowA * b_cols + colB] = sum;
            }
        }
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {

    if(a_rows == 0 || a_cols == 0 || b_cols == 0)
        return NULL;

    double** ruh = (double**)malloc(a_rows * sizeof(double*));
    for (uint32_t i = 0; i < a_rows; i++) {
        ruh[i] = (double*)malloc(b_cols * sizeof(double));
    }

    for (uint32_t rowA = 0; rowA < a_rows; rowA++) {
        for (uint32_t colB = 0; colB < b_cols; colB++) {

            ruh[rowA][colB] = 0.0;

            for (uint32_t colA = 0; colA < a_cols; colA++) {
                ruh[rowA][colB] += a[rowA][colA] * b[colA][colB];
            }
        }
    }

    return ruh;
}

double** createSubMatrix(
    double** a, 
    const uint32_t a_rows,
    const uint32_t a_cols,
    const uint32_t row_x, 
    const uint32_t col_y) {

        
        if(row_x >= a_rows || col_y >= a_cols){
            return a;
        }
        if(a_rows == 0|| a_cols == 0 || a_rows == 1 || a_cols == 1)
            return NULL;


    double** ruh = (double**)malloc((a_rows - 1) * sizeof(double*));

    for (int i = 0; i < a_rows - 1; i++) {
        ruh[i] = (double*)malloc((a_cols - 1) * sizeof(double));
    }


            for (int i = 0, oth = 0; i < a_rows; i++){
                if(row_x == i){ 
                    continue;
                }
                for(int col = 0, oCol = 0; col < a_cols; col++){
                    if(col_y == col) {
                            continue;
                        }
                    ruh[oth][oCol] = a[i][col];
                    oCol++;
                }
                oth++;
                }
                return ruh;
    }