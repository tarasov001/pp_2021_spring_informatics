// Copyright 2021 Prokofeva Elizaveta
#include "../../../modules/task_2/prokofeva_e_sparse_crs_omp/sparse_crs.h"
#include <omp.h>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

crs_matrix generate(int size)
{
    crs_matrix result;
    result.N = size;
    std::vector<double> vals;
    std::vector<int> columns, indx;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> dis(-100, 100);
    indx.emplace_back(0);
    for (int i = 0; i < size; ++i) {
      
        vals.emplace_back(dis(gen));
        columns.emplace_back(gen() % size);
        indx.emplace_back(static_cast<int>(vals.size()));
  
    }
    result.cols = columns;
    result.values = vals;
    result.row_index = indx;
    for (int i = 0; i < size; ++i) {
    
        std::cout <<"val  "<< vals[i] << std::endl;
        std::cout <<"col   "<< columns[i] << std::endl;
        
       
    }
   for (int i = 0; i < size+1; i++)
   {
       std::cout <<"row ind  "<< indx[i] << std::endl;
   }

    return result;
}



crs_matrix create(int size, std::vector<double> matrix) {
    crs_matrix result;
    result.N = size;

    result.row_index.push_back(0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[size * i + j] != 0) {
                result.values.push_back(matrix[size * i + j]);
                result.cols.push_back(j);
            }
        }
        result.row_index.push_back(result.values.size());
    }

    return result;
}

crs_matrix transpose(crs_matrix matrix) {
    crs_matrix Tmatrix;
    int N = Tmatrix.N = matrix.N;
    Tmatrix.row_index = std::vector<int>(static_cast<size_t>(N + 1));
    Tmatrix.values = std::vector<double>(static_cast<size_t>(matrix.values.size()));
    Tmatrix.cols = std::vector<int>(static_cast<size_t>(matrix.cols.size()));

    for (size_t i = 0; i < matrix.values.size(); i++) {
        Tmatrix.row_index[matrix.cols[i] + 1]++;
    }

    double s = 0;
    for (int i = 1; i <= N; i++) {
        int temp = Tmatrix.row_index[i];
        Tmatrix.row_index[i] = s;
        s += temp;
    }

    for (int i = 0; i < N; i++) {
        int j1 = matrix.row_index[i];
        int j2 = matrix.row_index[i + 1];
        int col = i;
        for (int j = j1; j < j2; j++) {
            double V = matrix.values[j];
            int r_index = matrix.cols[j];
            int i_index = Tmatrix.row_index[r_index + 1];
            Tmatrix.values[i_index] = V;
            Tmatrix.cols[i_index] = col;
            Tmatrix.row_index[r_index + 1]++;
        }
    }
    return Tmatrix;
}

double scalar_mult(crs_matrix first, crs_matrix second, int i, int j) {
    double summ = 0.0;
    for (int k = first.row_index[i]; k < first.row_index[i + 1]; k++) {
        for (int l = second.row_index[j]; l < second.row_index[j + 1]; l++) {
            if (first.cols[k] == second.cols[l]) {
                summ += first.values[k] * second.values[l];
                break;
            }
        }
    }
    return summ;
}

crs_matrix mult(crs_matrix first, crs_matrix second) {
    crs_matrix result;
    second = transpose(second);
    double summ;
    int rowNZ = 0;


    result.row_index.push_back(0);
    for (int i = 0; i < first.N; i++) {
        for (int j = 0; j < second.N; j++) {
            summ = scalar_mult(first, second, i, j);
            if (summ != 0) {
                result.values.push_back(summ);
                result.cols.push_back(j);
                rowNZ++;
            }
        }
        result.row_index.push_back(result.row_index[i] + rowNZ);
    }
    return result;
}
