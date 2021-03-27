// Copyright 2021 Kuznetsov Nikita
#include <gtest/gtest.h>
#include <vector>
#include "./sparse_matrix.h"
#define SIZE 100

TEST(MULTIPLY_SPARSE_MATRIX, THROWS_WHEN_SIZE_IS_NEGATIVE) {
  ASSERT_ANY_THROW(randMat(-10, -10));
}

TEST(MULTIPLY_SPARSE_MATRIX, THROWS_WHEN_SIZE_IS_ZERO) {
  ASSERT_ANY_THROW(randMat(0, 0));
}

TEST(MULTIPLY_SPARSE_MATRIX, SOLUTION_EQUAL_EXPECTED_RESULT) {
  sparseMatrix A = CCS(std::vector<double>{0, 0, 1, 0, 2, 0, 0, 0, 3, 0, 0, 0}, 3, 4);
  sparseMatrix B = CCS(std::vector<double>{3, 0, 0, 0, 4, 0}, 2, 3);
  std::vector<double> exp_res = { 4, 0, 0, 0, 12, 0, 0, 0 };
  std::vector<double> res = A * B;
  ASSERT_EQ(res, exp_res);
}

TEST(MULTIPLY_SPARSE_MATRIX, SOLUTION_WITH_50_ELEM_NO_THROW) {
  sparseMatrix A, B;
  A = CCS(randMat(50, 50), 50, 50);
  B = CCS(randMat(50, 50), 50, 50);
  std::vector<double> res = A * B;
  ASSERT_NO_THROW(res);
}

TEST(MULTIPLY_SPARSE_MATRIX, SOLUTION_WITH_N_ELEM_NO_THROW) {
  sparseMatrix A, B;
  A = CCS(randMat(SIZE, SIZE), SIZE, SIZE);
  B = CCS(randMat(SIZE, SIZE), SIZE, SIZE);
  std::vector<double> res = A * B;
  ASSERT_NO_THROW(res);
}
