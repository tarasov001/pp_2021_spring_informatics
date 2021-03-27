// Copyright 2021 Kuznetsov Nikita
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_1/kuznetsov_n_mult_sparse_mat/sparse_matrix.h"

std::vector<double> randMat(const int rows, const int cols) {
  if (rows <= 0 || cols <= 0) {
    throw - 1;
  }
  std::srand(std::time(nullptr));
  std::vector<double> res(cols * rows);
  for (int i = 0; i < rows * cols; i++) {
    double val_rand = static_cast<double>(std::rand() % 50 + 1);
    if (val_rand < 4) {
      res[i] = val_rand;
    } else {
      res[i] = 0;
    }
  }
  return res;
}

sparseMatrix CCS(const std::vector<double> new_mat, const int new_cols, const int new_rows) {
  if (new_cols <= 0 || new_rows <= 0) {
    throw - 1;
  }
  sparseMatrix res;
  res.cols = new_cols;
  res.rows = new_rows;
  res.not_null = 0;
  res.JA.push_back(0);
  for (int column = 0; column < new_cols; column++) {
    int not_null_count = 0;
    for (int i = column; i <= (new_rows - 1) * new_cols + column;
      i += new_cols) {
      if (new_mat[i] != 0) {
        not_null_count++;
        res.val.push_back(new_mat[i]);
        res.IA.push_back((i - column) / new_cols);
      }
    }
    res.JA.push_back(res.JA.back() + not_null_count);
    res.not_null += not_null_count;
  }
  return res;
}

const std::vector<double> operator*(const sparseMatrix& A, const sparseMatrix& B) {
  if (A.cols != B.rows) {
    throw - 1;
  }
  std::vector<double> result(A.rows * B.cols, 0);
  for (int col = 0; col < A.cols; col++) {
    for (int b_col = 0; b_col < B.cols; b_col++) {
      for (int i = A.JA[col]; i <= A.JA[col + 1] - 1; i++) {
        if (B.JA[b_col + 1] - B.JA[b_col] == 0) {
          continue;
        }
        for (int j = B.JA[b_col]; j <= B.JA[b_col + 1] - 1; j++) {
          if (B.IA[j] == col) {
            result[A.IA[i] * B.cols + b_col] += A.val[i] * B.val[j];
          }
        }
      }
    }
  }
  return result;
}
