// Copyright 2021 Tarasov Nikita
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/tarasov_n_gaussian_filter/gaussian_filter.h"

TEST(Gaussian_filter, Test1) {
    ASSERT_ANY_THROW(get_random_img(0, 1));
}

TEST(Gaussian_filter, Test2) {
    int height = 10;
    int width = 10;
    std::vector<double> img(height * 3);
    ASSERT_ANY_THROW(gaussian_filter(img, width, height, 1.0));
}

TEST(Gaussian_filter, Test3) {
    int height = 2;
    int width = 2;
    std::vector<double> img(width * height);
    ASSERT_ANY_THROW(gaussian_filter(img, width, height, 1.0));
}

TEST(Gaussian_filter, Test4) {
    std::vector<double> empty_img(13);
    ASSERT_ANY_THROW(gaussian_filter(empty_img, 13, 13, 1.0));
}

TEST(Gaussian_filter, Test5) {
    std::vector<double> img = get_random_img(400, 200);
    ASSERT_NO_THROW(gaussian_filter(img, 400, 200, 1.0));
}

TEST(Gaussian_filter, Test6) {
    std::vector<double> core;
    core = gaussian_core(1.0);
    double sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += core[i];
    }
    ASSERT_EQ(sum, 1);
}

TEST(Gaussian_filter, Test7) {
    std::vector<double> img = {
        252, 2, 108, 193, 237,
        2, 209, 184, 82, 92,
        210, 10, 6, 66, 116,
        212, 14, 23, 212, 201,
        164, 205, 160, 255, 151
    };

    std::vector<double> expectation = {
        252, 2, 108, 193, 237,
        2, 101, 93, 102, 92,
        210, 83, 64, 89, 116,
        212, 74, 122, 142, 201,
        164, 205, 160, 255, 151
    };
    img = gaussian_filter(img, 5, 5, 1.0);
    ASSERT_EQ(img, expectation);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
