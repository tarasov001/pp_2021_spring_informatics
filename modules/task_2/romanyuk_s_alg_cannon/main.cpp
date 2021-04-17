// Copyright 2021 Romanyuk Sergey
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include "../../../modules/task_2/romanyuk_s_alg_cannon/cannon.h"

TEST(Cannon_Multiplication, TEST_1) {
    std::vector<double> A = genMatrix(16);

    std::vector<double> B = genMatrix(16);

    std::vector<double> res1 = SequentinalMultiMatrix(A, B, 16);

    std::vector<double> res2 = CannonMultiplication(A, B, 4);

    ASSERT_EQ(res1, res2);
}

TEST(Cannon_Multiplication, TEST_2) {
    std::vector<double> A = genMatrix(36);

    std::vector<double> B = genMatrix(36);

    std::vector<double> res1 = SequentinalMultiMatrix(A, B, 36);

    std::vector<double> res2 = parallelCannonMult(A, B, 4);

    ASSERT_EQ(res1, res2);
}

TEST(Cannon_Multiplication, TEST_3) {
    std::vector<double> A = genMatrix(100);

    std::vector<double> B = genMatrix(100);
    double t1 = omp_get_wtime();
    std::vector<double> res1 = SequentinalMultiMatrix(A, B, 4);
    double t2 = omp_get_wtime();
    std::cout << "Direct: " << t2 - t1 << "\n";
    t1 = omp_get_wtime();
    std::vector<double> res2 = parallelCannonMult(A, B, 4);
    t2 = omp_get_wtime();
    std::cout << "OMP: " << t2 - t1 << "\n";

    ASSERT_EQ(res1, res2);
}

TEST(Cannon_Multiplication, TEST_4) {
    std::vector<double> A = genMatrix(4);

    std::vector<double> B = genMatrix(4);

    ASSERT_ANY_THROW(parallelCannonMult(A, B, -2));
}

TEST(Cannon_Multiplication, TEST_5) {
    std::vector<double> A = genMatrix(4);

    std::vector<double> B = genMatrix(4);

    ASSERT_ANY_THROW(CannonMultiplication(A, B, 10));
}
