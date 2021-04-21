// Copyright 2021 Paranicheva Alyona
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include "./labeling.h"

using namespace std;

TEST(CLabeling, 4x5) {
    int rows = 4;
    int cols = 5;
    const std::vector<int> img = {
        0, 0, 0, 0, 0,
        0, 0, 0, 1, 0,
        0, 1, 1, 0, 0,
        0, 0, 0, 0, 0,
    };
    std::vector<int> expres = CLabeling(img, rows, cols);
    std::vector<int> res = CLabelingOmp(img, rows, cols);
    ASSERT_EQ(expres, res);
}

TEST(CLabeling, 4x7) {
    int rows = 4;
    int cols = 7;
    const std::vector<int> img = getRandomMatrix(rows, cols);
    std::vector<int> expres = CLabeling(img, rows, cols);
    std::vector<int> res = CLabelingOmp(img, rows, cols);
    ASSERT_EQ(expres, res);
}

TEST(CLabeling, 5x16) {
    int rows = 5;
    int cols = 16;

    const std::vector<int> img = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    std::vector<int> expres = CLabeling(img, rows, cols);
    std::vector<int> res = CLabelingOmp(img, rows, cols);
    ASSERT_EQ(expres, res);
}

TEST(CLabeling, 5x12) {
    int rows = 5;
    int cols = 12;
    const std::vector<int> img = getRandomMatrix(rows, cols);
    std::vector<int> expres = CLabeling(img, rows, cols);
    std::vector<int> res = CLabelingOmp(img, rows, cols);
    ASSERT_EQ(expres, res);

}

TEST(Clabeling_Matrix_gen, Invalid_size) {
    int rows = -5;
    int cols = 7;
    ASSERT_ANY_THROW(getRandomMatrix(rows, cols));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
