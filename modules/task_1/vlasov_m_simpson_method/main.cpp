// Copyright 2021 Vlasov Maksim
// Задача 1.11. Вычисление многомерных интегралов с использованием многошаговой
// схемы (метод Симпсона).

#include <gtest/gtest.h>
#include <vector>
#include "./simpson_method.h"

TEST(Sequential_SimpsonMethodTest, can_integrate_single_dim_function) {
    ASSERT_TRUE(1);
}

TEST(Sequential_SimpsonMethodTest, can_integrate_two_dims_function) {
    ASSERT_TRUE(1);
}

TEST(Sequential_SimpsonMethodTest, cannot_accept_invalid_segment_vectors) {
    ASSERT_TRUE(1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
