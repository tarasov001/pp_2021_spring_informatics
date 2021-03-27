// Copyright 2021 Ludina Daria
#ifndef MODULES_TASK_1_LUDINA_D_SPARSE_MATRIX_COMPLEX_CCS_SPARSE_MATRIX_COMPLEX_CCS_H_
#define MODULES_TASK_1_LUDINA_D_SPARSE_MATRIX_COMPLEX_CCS_SPARSE_MATRIX_COMPLEX_CCS_H_

#include <vector>
#include <complex>
#include <random>
#include <ctime>

struct SparseMatrix {
  int rows, cols;
  std::vector<int> col_idx;
  std::vector<int> row;
  std::vector<std::complex<int>> value;

  SparseMatrix();
  SparseMatrix(int _rows, int _cols);
  SparseMatrix(int _rows, int _cols,
    const std::vector<std::complex<int>>& _value,
    const std::vector<int>& _col_idx, const std::vector<int>& _row);
  SparseMatrix(int _rows, int _cols, std::vector<std::complex<int>> matrix);
  SparseMatrix transpose();
};

SparseMatrix Multiplication(SparseMatrix A, SparseMatrix B);

#endif  // MODULES_TASK_1_LUDINA_D_SPARSE_MATRIX_COMPLEX_CCS_SPARSE_MATRIX_COMPLEX_CCS_H_
