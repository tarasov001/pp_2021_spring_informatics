// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <tbb/tbb.h>
#include "../../../modules/task_3/shagov_m_fox/fox.h"

TEST(Shagov_Maksim_Tbb, Test_4_on_4_Random_Matrix_Mult) {
     Matrix A = {1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4};
    Matrix B = {4, 3, 2, 1,
                4, 3, 2, 1,
                4, 3, 2, 1,
                4, 3, 2, 1};
    Matrix C = parallelBlockMatrixMultiplication(A, B, 4 * 4, 4);
    Matrix C_my_result = {40, 30, 20, 10,
                          40, 30, 20, 10,
                          40, 30, 20, 10,
                          40, 30, 20, 10};
    ASSERT_EQ(C_my_result, C);
}

TEST(Shagov_Maksim_Tbb, same_result_as_sequential) {
    size_t size = 1000;
    Matrix A = createRandomMatrix(size * size);
    Matrix B = createRandomMatrix(size * size);
    std::pair<tbb::tick_count, tbb::tick_count> time1, time2;
    time1.first = tbb::tick_count::now();
    Matrix C = parallelBlockMatrixMultiplication(A, B, size * size, 1);
    time1.second = tbb::tick_count::now();
    std::cout << "Sequential " << (time1.second - time1.first).seconds() << ' ' << std::endl;
    time2.first = tbb::tick_count::now();
    Matrix C_1 = parallelBlockMatrixMultiplication(A, B, size * size, 4);
    time2.second = tbb::tick_count::now();
    std::cout << "Parallel " << (time2.second - time2.first).seconds() << ' ' << std::endl;
    std::cout << "  " << (time1.second - time1.first).seconds() / (time2.second - time2.first).seconds() << std::endl;
    ASSERT_TRUE(isEqualMatrix(C, C_1));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
