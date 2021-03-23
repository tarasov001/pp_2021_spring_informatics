// Copyright 2021 Gruzdeva Diana

#include <gtest/gtest.h>
#include "../../../modules/task_1/gruzdeva_d_fox_mult/fox_mult.h"

TEST(Gruzdeva_Diana, CHECKING_DIRECT_MULTIPLICATION) {
    std::vector<double> A = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> B = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> C = {1, 4, 10, 20,
                             0, 1, 4, 10,
                             0, 0, 1, 4,
                             0, 0, 0, 1};

    std::vector<double> C_Calculated = directMultiplication(A, B);

    ASSERT_EQ(C_Calculated, C);
}

TEST(Gruzdeva_Diana, CHECKING_FOX_MULTIPLICATION) {
    std::vector<double> A = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> B = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> C = {1, 4, 10, 20,
                             0, 1, 4, 10,
                             0, 0, 1, 4,
                             0, 0, 0, 1};

    std::vector<double> C_Calculated = foxMultiplication(A, B, 2);

    ASSERT_EQ(C_Calculated, C);
}

TEST(Gruzdeva_Diana, CHECKING_FOX_MULTIPLICATION_DIFFERENT_BLOCK_SIZE) {
    std::vector<double> A = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> B = {1, 2, 3, 4,
                             0, 1, 2, 3,
                             0, 0, 1, 2,
                             0, 0, 0, 1};

    std::vector<double> C = {1, 4, 10, 20,
                             0, 1, 4, 10,
                             0, 0, 1, 4,
                             0, 0, 0, 1};

    std::vector<double> C_Calculated = foxMultiplication(A, B, 4);

    ASSERT_EQ(C_Calculated, C);
}

TEST(Gruzdeva_Diana, EQUALITY_OF_THESE_METHODS) {
    std::vector<double> A = getRandomMatrix(4, time(0));

    std::vector<double> B = getRandomMatrix(4, time(0) + 1);

    std::vector<double> C1 = directMultiplication(A, B);

    std::vector<double> C2 = foxMultiplication(A, B, 2);

    ASSERT_EQ(C1, C2);
}

TEST(Gruzdeva_Diana, DIFFERENT_BLOCK_SIZE) {
    std::vector<double> A = getRandomMatrix(4, time(0));

    std::vector<double> B = getRandomMatrix(4, time(0) + 1);

    std::vector<double> C1 = foxMultiplication(A, B, 4);

    std::vector<double> C2 = foxMultiplication(A, B, 2);

    ASSERT_EQ(C1, C2);
}
