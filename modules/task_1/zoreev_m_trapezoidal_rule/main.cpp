// Copyright 2021 Zoreev Mikhail

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../../../modules/task_1/zoreev_m_trapezoidal_rule/trapezoidal_rule.h"

TEST(Sequential_TrapezoidalRule, Can_Integrate_2Dimensional) {
    std::vector<double> from = {0, 0};
    std::vector<double> to = {1, 1};
    double result = integrate([](std::vector<double> args) {
        return std::sin(args[0]) * args[1];
        },
        from, to, 200);
    ASSERT_NEAR(0.22984884706593, result, 1e-2);
}

TEST(Sequential_TrapezoidalRule, Can_Integrate_3Dimensional) {
    std::vector<double> from = {0, 0};
    std::vector<double> to = {1, 1};
    double result = integrate([](std::vector<double> args) {
        return args[0] * args[0] + args[1] + args[1];
        },
        from, to, 200);
    ASSERT_NEAR(1.33333333333333, result, 1e-2);
}

TEST(Sequential_TrapezoidalRule, Blank_1) {
}

TEST(Sequential_TrapezoidalRule, Blank_2) {
}

TEST(Sequential_TrapezoidalRule, Blank_3) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
