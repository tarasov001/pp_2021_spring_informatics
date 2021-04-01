// Copyright 2021 Kumbrasev Mark
#include <gtest/gtest.h>
#include "./conjugate_gradient.h"

TEST(Conjugate_gradient, M2) {
    vector<vector<double>> M = { { 5, 2}, {2, 1} };
    vector<double> B = { 7, 9 };

    vector<double> X = ConjugateGradient( M, B );
    vector<double> res = mMultv( M, X );
    
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(res[i], B[i]);
    }
}
TEST(Conjugate_gradient, X) {
    vector<vector<double>> M = { { 2, 3, -1 }, {1, -2, 1 }, { 1, 0, 2 } };
    vector<double> B = { 9, 3, 2 };

    vector<double> X = ConjugateGradient( M, B );
    vector<double> res = { 4, 0, -1 };
    
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(res[i], X[i]);
    }
}
TEST(Conjugate_gradient, M3) {
    vector<vector<double>> M = { { 2, 3, -1 }, {1, -2, 1 }, { 1, 0, 2 } };
    vector<double> B = { 9, 3, 2 };

    vector<double> X = ConjugateGradient( M, B );
    vector<double> res = mMultv( M, X );
    
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(B[i], res[i], 0.05);
    }
}
TEST(Conjugate_gradient, M4) {
    vector<vector<double>> M = { { 1, -1, 3, 1 }, {4, -1, 5, 4 }, { 2, -2, 4, 1 }, { 1, -4, 5, -1 } };
    vector<double> B = { 5, 4, 6, 3 };

    vector<double> X = ConjugateGradient( M, B );
    vector<double> res = mMultv( M, X );
    
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NE(B[i], res[i]);
    }
}
TEST(Conjugate_gradient, MultiMB) {
    vector<vector<double>> M = { { 2, 6, 1 }, { 3, 1, 7 }, { 8, 9, 1 } };
    vector<double> B = { 7, 4, 1 };

    vector<double> res = mMultv( M, B );
    vector<double> I = { { 39, 32, 93 } };
    
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(I[i], res[i]);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
