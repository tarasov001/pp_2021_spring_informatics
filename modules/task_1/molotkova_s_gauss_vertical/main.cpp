// Copyright 2021 Molotkova Svetlana
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "./vert_gauss.h"

TEST(Matrix_testing, invalid_argument1) {
  int rows = 0;
  int cols = 0;
  ASSERT_ANY_THROW(matrixCreation(rows, cols));
}

TEST(Matrix_testing, invalid_argument2) {
  int rows = -1;
  int cols = 2;
  ASSERT_ANY_THROW(matrixCreation(rows, cols));
}

TEST(Gauss_filter, 1x1) {
  int rows = 1;
  int cols = 1;
  std::vector<double> matrix = matrixCreation(rows, cols);
  matrix = transpose(matrix, rows, cols);
  std::swap(cols, rows);
  ASSERT_NO_THROW(gaussFilter(matrix, rows, cols, 1, 5));
}

TEST(Gauss_filter, 11x165) {
  int rows = 11;
  int cols = 165;
  std::vector<double> matrix = matrixCreation(rows, cols);
  matrix = transpose(matrix, rows, cols);
  std::swap(cols, rows);
  ASSERT_NO_THROW(gaussFilter(matrix, rows, cols, 1, 5));
}

TEST(Gauss_filter, 21x19) {
  int rows = 21;
  int cols = 19;
  std::vector<double> matrix = matrixCreation(rows, cols);
  matrix = transpose(matrix, rows, cols);
  std::swap(cols, rows);
  ASSERT_NO_THROW(gaussFilter(matrix, rows, cols, 1, 5));
}

TEST(Gauss_filter, 163x1) {
  int rows = 163;
  int cols = 1;
  std::vector<double> matrix = matrixCreation(rows, cols);
  matrix = transpose(matrix, rows, cols);
  std::swap(cols, rows);
  ASSERT_NO_THROW(gaussFilter(matrix, rows, cols, 1, 5));
}

TEST(Gauss_filter, 36x18) {
  int rows = 36;
  int cols = 18;
  std::vector<double> matrix = matrixCreation(rows, cols);
  matrix = transpose(matrix, rows, cols);
  std::swap(cols, rows);
  ASSERT_NO_THROW(gaussFilter(matrix, rows, cols, 1, 5));
}
