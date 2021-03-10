// Copyright 2021 Denis Ostapovich
#include <gtest/gtest.h>
#include <vector>
#include "./gaussian_blur.h"

TEST(Sequential_Gaussian_blur, GetRandomMatrix_Throws_On_Zero_Args) {
    ASSERT_ANY_THROW(getRandomMatrix(0, 0));
}

TEST(Sequential_Gaussian_blur, GetRandomMatrix_Throws_On_Negative_Args) {
    ASSERT_ANY_THROW(getRandomMatrix(-1, -1));
}

TEST(Sequential_Gaussian_blur, GetRandomMatrix_No_Throw_On_Valid_Args) {
    ASSERT_NO_THROW(getRandomMatrix(3, 5));
}

TEST(Sequential_Gaussian_blur, GetRandomMatrix_Returns_Vector_Of_Valid_Size) {
    std::vector<uint8_t> vec = getRandomMatrix(2, 7);
    ASSERT_EQ(vec.size(), (size_t)14);
}

TEST(Sequential_Gaussian_blur, CalculateCore_Returns_Valid_Core) {
    double core[3][3];
    calculateCore(core);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ASSERT_NE(core[i][j], 0);
        }
    }
}

TEST(Sequential_Gaussian_blur, ApplyFilter_Throws_On_Zero_Size_Matrix) {
    std::vector<uint8_t> mat;
    ASSERT_ANY_THROW(applyFilter(mat, 10));
}

TEST(Sequential_Gaussian_blur, ApplyFilter_Throws_On_Zero_Or_Negative_Width_Value) {
    std::vector<uint8_t> mat = getRandomMatrix(10, 20);
    ASSERT_ANY_THROW(applyFilter(mat, 0));
    ASSERT_ANY_THROW(applyFilter(mat, -1));
}

TEST(Sequential_Gaussian_blur, ApplyFilter_Throws_Invalid_Width_Value) {
    std::vector<uint8_t> mat = getRandomMatrix(10, 20);
    ASSERT_ANY_THROW(applyFilter(mat, 3));
}

TEST(Sequential_Gaussian_blur, ApplyFilter_No_Throw_On_Valid_Args) {
    std::vector<uint8_t> mat = getRandomMatrix(10, 20);
    ASSERT_NO_THROW(applyFilter(mat, 10));
}
