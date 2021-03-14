// Copyright 2021 Shagov Maksim
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/shagov_m_fox/fox.h"

TEST(Shagov_Maksim_Sequential, Test_Create_Random_Matrix) {
    const int count = 10;
    Matrix A = createRandomMatrix(count);
    Matrix B(A);
    ASSERT_EQ(A, B);
}

TEST(Shagov_Maksim_Sequential, Test_Throw_Exeption_Dif_Size) {
    Matrix A = {1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};
    Matrix B(1);
    ASSERT_ANY_THROW(sequentialMatrixmultiplication(A, B, 4));
}

TEST(Shagov_Maksim_Sequential, Test_Throw_Exeption_Null_Block_Size) {
    Matrix A;
    Matrix B;
    ASSERT_ANY_THROW(sequentialMatrixmultiplication(A, B, 0));
}

TEST(Shagov_Maksim_Sequential, Test_Throw_Exeption_Null_Matrix_Size) {
    Matrix A;
    Matrix B;
    ASSERT_ANY_THROW(sequentialMatrixmultiplication(A, B, 10));
}

TEST(Shagov_Maksim_Sequential, Test_Identity_Matrix_Mult) {
    Matrix A = {1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};
    Matrix B(A);
    Matrix C = sequentialMatrixmultiplication(A, B, 4);
    ASSERT_EQ(A, C);
}

TEST(Shagov_Maksim_Sequential, Test_Top_Matrix_Mult) {
    Matrix A = {1, 2, 3, 4,
                0, 2, 3, 4,
                0, 0, 3, 4,
                0, 0, 0, 4};
    Matrix B(A);
    Matrix C = sequentialMatrixmultiplication(A, B, 4);
    Matrix C_my_result = {1, 6, 18, 40,
                          0, 4, 15, 36,
                          0, 0, 9,  28,
                          0, 0, 0,  16,};
    ASSERT_EQ(C_my_result, C);
}

TEST(Shagov_Maksim_Sequential, Test_4_on_4_Some_Matrix_Mult) {
    Matrix A = {1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4};
    Matrix B(A);
    Matrix C = sequentialMatrixmultiplication(A, B, 4);
    ASSERT_EQ(A, B);
}

TEST(Shagov_Maksim_Sequential, Test_4_on_4_Reverse_Matrix_Mult) {
    Matrix A = {1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4};
    Matrix B = {4, 3, 2, 1,
                4, 3, 2, 1,
                4, 3, 2, 1,
                4, 3, 2, 1};
    Matrix C = sequentialMatrixmultiplication(A, B, 4);
    Matrix C_my_result = {40, 30, 20, 10,
                          40, 30, 20, 10,
                          40, 30, 20, 10,
                          40, 30, 20, 10};
    ASSERT_EQ(C_my_result, C);
}

TEST(Shagov_Maksim_Sequential, Test_4_on_4_Matrix_Mult) {
    Matrix A = {4,	  18,	 7,	  -2,
                0,	  12,	 1.3,  -5.7,
                0.01, 1.2,	-1.2, -4,
                0.3,  0,	 7,	  -2.5};
    Matrix B = {4.3,  -150,   14.14, 5.1,
                1,	  -1,     0,	-2,
                2,	   15.6,  6.15,	 14.88,
                88.14, 2.5,	 -7.3,	 5};
    Matrix C = sequentialMatrixmultiplication(A, B, 4);
    Matrix C_my_result = {-127.08,	-513.8,	114.21,   78.56,
                          -487.798,	-5.97,	49.605,	 -33.156,
                          -353.717,	-31.42,	21.9614, -40.205,
                          -205.06,	 57.95,	65.542,	  93.19};
    ASSERT_TRUE(isEqualMatrix(C_my_result, C));
}

