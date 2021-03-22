// Copyright 2021 Prokofeva Elizaveta
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/prokofeva_e_sparse_crs/sparse_crs.h"


TEST(Sparse_crs_matrix_1, Create) {
    std::vector<double> a = { 0, 3, 0, 7,
                              0, 0, 8, 0,
                              0, 0, 0, 0,
                              9, 0, 15, 16};
    crs_matrix A = create(4, a);
    std::vector<double> value = { 3, 7, 8, 9, 15, 16 };
    std::vector<int> col = { 1, 3, 2, 0, 2, 3 };
    std::vector<int> rowIndex = { 0, 2, 3, 3, 6 };
    ASSERT_EQ(A.values, value);
    ASSERT_EQ(A.cols, col);
    ASSERT_EQ(A.row_index, rowIndex);
}
TEST(Sparse_crs_matrix_2, Transposition) {
    std::vector<double> a = { 0, 3, 0, 7,
                              0, 0, 8, 0,
                              0, 0, 0, 0,
                              9, 0, 15, 16 };
    crs_matrix A = create(4, a);
    A = transpose(A);
    std::vector<double> value = { 9, 3, 8, 15, 7, 16 };
    std::vector<int> col = { 3, 0, 1, 3, 0, 3 };
    std::vector<int> rowIndex = { 0, 1, 2, 4, 6 };
    ASSERT_EQ(A.values, value);
    ASSERT_EQ(A.cols, col);
    ASSERT_EQ(A.row_index, rowIndex);
}
TEST(Sparse_crs_matrix_3, Multiplication_3x3) {
    std::vector<double> a = { 0, 2, 0,
                             10, 0, 0,
                              0, 0, 6};
    crs_matrix A = create(3, a);
    std::vector<double> b = { 1, 0, 0,
                              0, 5, 0,
                              0, 14, 3};
    crs_matrix B = create(3, b);
    crs_matrix C = mult(A, B);
    std::vector<double> c = { 10, 10, 84, 18 };
    ASSERT_EQ(C.values, c);
}
TEST(Sparse_crs_matrix_4, Multiplication_3x3) {
    std::vector<double> a = { 0, 0.5, 1.5,
                              2, 0, 0,
                              0, 6.5, 0};
    crs_matrix A = create(3, a);
    std::vector<double> b = { 3.5, 0, 0,
                               0, 1, 4.5,
                               0, 0, 0};
    crs_matrix B = create(3, b);
    crs_matrix C = mult(A, B);
    std::vector<double> c = { 0.5, 2.25, 7, 6.5, 29.25 };
    ASSERT_EQ(C.values, c);
}
TEST(Sparse_crs_matrix_5, Multiplication_4x4) {
    std::vector<double> a = { 0, 11, 0, 25,
                              96, 0, 0, 0,
                              0, 0, 15, 0,
                              0, 44, 0, 0};
    crs_matrix A = create(4, a);
    std::vector<double> b = { 57, 63, 0, 0,
                              0, 0, 41, 0,
                              0, 78, 0, 0,
                              0, 0, 0, 22};
    crs_matrix B = create(4, b);
    crs_matrix C = mult(A, B);
    std::vector<double> c = { 451, 550, 5472, 6048, 1170, 1804 };
    ASSERT_EQ(C.values, c);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
