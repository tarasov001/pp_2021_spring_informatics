// Copyright 2021 Prokofeva Elizaveta
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../../../modules/task_2/prokofeva_e_sparse_crs_omp/sparse_crs.h"

TEST(Sparse_crs_matrix, Test1) {
    crs_matrix first = generate(50);
    crs_matrix second = generate(50);

    double  seq_t_1 = omp_get_wtime();
    crs_matrix res = mult(first, second);
    double seq_t_2 = omp_get_wtime();
    std::cout << "Sequential time = " << seq_t_2 - seq_t_1 << "\n";

    double par_t_1 = omp_get_wtime();
    crs_matrix resp = parallel_mult(first, second);
    double par_t_2 = omp_get_wtime();
    std::cout << "OpenMP time = " << par_t_2 - par_t_1 << "\n";

    ASSERT_EQ(resp.values, res.values);
    ASSERT_EQ(resp.cols, res.cols);
    ASSERT_EQ(resp.row_index, res.row_index);
}
TEST(Sparse_crs_matrix, Test2) {
    crs_matrix first = generate(100);
    crs_matrix second = generate(100);

    double  seq_t_1 = omp_get_wtime();
    crs_matrix res = mult(first, second);
    double seq_t_2 = omp_get_wtime();
    std::cout << "Sequential time = " << seq_t_2 - seq_t_1 << "\n";

    double par_t_1 = omp_get_wtime();
    crs_matrix resp = parallel_mult(first, second);
    double par_t_2 = omp_get_wtime();
    std::cout << "OpenMP time = " << par_t_2 - par_t_1 << "\n";

    ASSERT_EQ(resp.values, res.values);
    ASSERT_EQ(resp.cols, res.cols);
    ASSERT_EQ(resp.row_index, res.row_index);
}
TEST(Sparse_crs_matrix, Test3) {
    crs_matrix first = generate(200);
    crs_matrix second = generate(200);

    double  seq_t_1 = omp_get_wtime();
    crs_matrix res = mult(first, second);
    double seq_t_2 = omp_get_wtime();
    std::cout << "Sequential time = " << seq_t_2 - seq_t_1 << "\n";

    double par_t_1 = omp_get_wtime();
    crs_matrix resp = parallel_mult(first, second);
    double par_t_2 = omp_get_wtime();
    std::cout << "OpenMP time = " << par_t_2 - par_t_1 << "\n";

    ASSERT_EQ(resp.values, res.values);
    ASSERT_EQ(resp.cols, res.cols);
    ASSERT_EQ(resp.row_index, res.row_index);
}
TEST(Sparse_crs_matrix, Test4) {
    crs_matrix first = generate(350);
    crs_matrix second = generate(350);

    double  seq_t_1 = omp_get_wtime();
    crs_matrix res = mult(first, second);
    double seq_t_2 = omp_get_wtime();
    std::cout << "Sequential time = " << seq_t_2 - seq_t_1 << "\n";

    double par_t_1 = omp_get_wtime();
    crs_matrix resp = parallel_mult(first, second);
    double par_t_2 = omp_get_wtime();
    std::cout << "OpenMP time = " << par_t_2 - par_t_1 << "\n";

    ASSERT_EQ(resp.values, res.values);
    ASSERT_EQ(resp.cols, res.cols);
    ASSERT_EQ(resp.row_index, res.row_index);
}
TEST(Sparse_crs_matrix, Test5) {
    crs_matrix first = generate(500);
    crs_matrix second = generate(500);

    double  seq_t_1 = omp_get_wtime();
    crs_matrix res = mult(first, second);
    double seq_t_2 = omp_get_wtime();
    std::cout << "Sequential time = " << seq_t_2 - seq_t_1 << "\n";

    double par_t_1 = omp_get_wtime();
    crs_matrix resp = parallel_mult(first, second);
    double par_t_2 = omp_get_wtime();
    std::cout << "OpenMP time = " << par_t_2 - par_t_1 << "\n";

    ASSERT_EQ(resp.values, res.values);
    ASSERT_EQ(resp.cols, res.cols);
    ASSERT_EQ(resp.row_index, res.row_index);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
