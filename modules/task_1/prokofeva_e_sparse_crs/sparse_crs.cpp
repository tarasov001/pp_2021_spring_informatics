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
    int N = Tmatrix.N = matrix.N;
    Tmatrix.row_index = std::vector<int>(static_cast<size_t>(matrix.N + 1));
    Tmatrix.values = std::vector<double>(static_cast<size_t>(matrix.values.size()));
    Tmatrix.cols = std::vector<int>(static_cast<size_t>(matrix.cols.size()));
    int size = matrix.values.size();
    for (size_t i = 0; i < size; i++) {
        int col = matrix.cols[i];
        Tmatrix.row_index[col + 1]++;
    }

    double s = 0;
    for (int i = 1; i <= N; i++) {
        int tmp = Tmatrix.row_index[i];
        Tmatrix.row_index[i] = s;
        s += tmp;
    }

    for (int i = 0; i < N; i++) {
        for (int j = matrix.row_index[i]; j < matrix.row_index[i + 1]; j++) {
            Tmatrix.values[Tmatrix.row_index[matrix.cols[j] + 1]] = matrix.values[j];
            Tmatrix.cols[Tmatrix.row_index[matrix.cols[j] + 1]] = i;
            Tmatrix.row_index[matrix.cols[j] + 1]++;
        }
    }
    return Tmatrix;
}

double scalar_mult(crs_matrix A, crs_matrix B, int i, int j) {
    double sum = 0.0;
    int a = A.row_index[i];
    int a1 = A.row_index[i + 1];
    int b = B.row_index[j];
    int b1 = B.row_index[j + 1];
    for (int k = a; k < a1; k++) {
        for (int l = b; l < b1; l++) {
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
    int rowNZ = 0;
    int tmp = 0;

    result.row_index.emplace_back(tmp);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum = scalar_mult(A, B, i, j);
            if (sum != 0) {
                result.cols.emplace_back(j);
                result.values.emplace_back(sum);
                rowNZ++;
            }
        }
        result.row_index.emplace_back(rowNZ + result.row_index[i]);
    }
    return result;
}
