// Copyright 2021 Prokofeva Elizaveta
#include "../../../modules/task_1/prokofeva_e_sparse_crs/sparse_crs.h"
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

crs_matrix create(int size, std::vector<double> mat) {
    crs_matrix res;
    res.N = size;

    res.row_index.push_back(0);
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (mat[res.N * i + j] != 0) {
                count++;
                res.values.push_back(mat[size * i + j]);
                res.cols.push_back(j);
            }
        }
        count += res.row_index.back();
        res.row_index.push_back(res.cols.size());
    }

    return res;
}

crs_matrix transpose(crs_matrix matrix) {
    crs_matrix Tmatrix;
    Tmatrix.N = matrix.N;
    Tmatrix.row_index = std::vector<int>(static_cast<size_t>(matrix.N + 1));
    Tmatrix.values = std::vector<double>(static_cast<size_t>(matrix.values.size()));
    Tmatrix.cols = std::vector<int>(static_cast<size_t>(matrix.cols.size()));

    for (size_t i = 0; i < matrix.values.size(); i++) {
        Tmatrix.row_index[matrix.cols[i] + 1]++;
    }

    double s = 0;
    for (int i = 1; i <= matrix.N; i++) {
        int tmp = Tmatrix.row_index[i];
        Tmatrix.row_index[i] = s;
        s += tmp;
    }

    for (int i = 0; i < matrix.N; i++) {
        for (int j = matrix.row_index[i]; j < matrix.row_index[i + 1]; j++) {
            int r_ind = matrix.cols[j];
            Tmatrix.values[Tmatrix.row_index[r_ind + 1]] = matrix.values[j];
            Tmatrix.cols[Tmatrix.row_index[r_ind + 1]] = i;
            Tmatrix.row_index[matrix.cols[j] + 1]++;
        }
    }
    return Tmatrix;
}

double scalar_mult(crs_matrix A, crs_matrix B, int i, int j) {
    double sum = 0.0;
    for (int k = A.row_index[i]; k < A.row_index[i + 1]; k++) {
        for (int l = B.row_index[j]; l < B.row_index[j + 1]; l++) {
            if (A.cols[k] == B.cols[l]) {
                
                sum += A.values[k] * B.values[l];
                break;
            }
        }
    }
    return sum;
}

crs_matrix mult(crs_matrix A, crs_matrix B) {
    int N = A.N;
    crs_matrix result;
    B = transpose(B);
    double sum;
    int rowNZ;

    result.row_index.push_back(0);
    for (int i = 0; i < N; i++) {
        rowNZ = 0;
        for (int j = 0; j < N; j++) {

            sum = scalar_mult(A, B, i, j);
            if (sum != 0) {
                result.cols.push_back(j);
                result.values.push_back(sum);
                rowNZ++;
            }
        }
        result.row_index.push_back(rowNZ + result.row_index[i]);
    }
    return result;
}
