// Copyright 2021 Prokofeva Elizaveta
#ifndef MODULES_TASK_1_PROKOFEVA_E_SPARSE_CRS_SPARSE_CRS_H_
#define MODULES_TASK_1_PROKOFEVA_E_SPARSE_CRS_SPARSE_CRS_H_

#include<vector>

struct crs_matrix
{
    int N;
    std::vector<double> values;
    std::vector<int> cols;
    std::vector<int> row_index;

};

crs_matrix transpose(crs_matrix A);
crs_matrix create(int size, std::vector<double> mat);
crs_matrix mult(crs_matrix A, crs_matrix B);
double scalar_mult(crs_matrix A, crs_matrix B, int i, int j);

#endif // MODULES_TASK_1_PROKOFEVA_E_SPARSE_CRS_SPARSE_CRS_H_