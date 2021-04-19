// Copyright 2021 Streltsova Yana

#include <gtest/gtest.h>

#include <algorithm>

#include "./Shell_sort.h"


TEST(Shell_sort_omp, Test_zero_size) {
    const int size_vector = 0;
    std::vector<int> a_parallel = getRandomVectorInt(size_vector);
    std::vector<int> result;
    shell_sort_parallel(a_parallel);
    ASSERT_EQ(result, a_parallel);
}

TEST(Shell_sort_omp, Test_one_element) {
    const int size_vector = 1;
    std::vector<int> a_parallel = getRandomVectorInt(size_vector);
    std::vector<int> result(a_parallel);
    shell_sort_parallel(a_parallel);
    ASSERT_EQ(result, a_parallel);
}

TEST(Shell_sort_omp, Test_sorted_vector) {
    const int size_vector = 100;
    std::vector<int> a_parallel = getRandomVectorInt(size_vector);
    std::sort(a_parallel.begin(), a_parallel.end());
    std::vector<int> result(a_parallel);
    shell_sort_parallel(a_parallel);
    ASSERT_EQ(result, a_parallel);
}

TEST(Shell_sort_omp, Test_normal_size) {
    const int size_vector = 100;
    std::vector<int> seq_a = getRandomVectorInt(size_vector);
    std::vector<int> parallel_a(seq_a);
    double t1, t2;

    t1 = omp_get_wtime();
    shell_sort_sequential(seq_a);
    t2 = omp_get_wtime();
    std::cout << "Sequential Time: " << t2 - t1 << std::endl;

    t1 = omp_get_wtime();
    shell_sort_parallel(parallel_a);
    t2 = omp_get_wtime();
    std::cout << "Parallel Time: " << t2 - t1 << std::endl;

    ASSERT_EQ(seq_a, parallel_a);
}


TEST(Shell_sort_omp, Test_big_size_int) {
    const int size_vector = 10000;
    std::vector<int> seq_a = getRandomVectorInt(size_vector);
    std::vector<int> parallel_a(seq_a);
    double t1, t2;

    t1 = omp_get_wtime();
    shell_sort_sequential(seq_a);
    t2 = omp_get_wtime();
    std::cout << "Sequential Time: " << t2 - t1 << std::endl;

    t1 = omp_get_wtime();
    shell_sort_parallel(parallel_a);
    t2 = omp_get_wtime();
    std::cout << "Parallel Time: " << t2 - t1 << std::endl;

    ASSERT_EQ(seq_a, parallel_a);
}

TEST(Shell_sort_omp, Test_big_size_double) {
    const int size_vector = 10000;
    std::vector<double> seq_a = getRandomVectorDouble(size_vector);
    std::vector<double> parallel_a(seq_a);
    double t1, t2;

    t1 = omp_get_wtime();
    shell_sort_sequential(seq_a);
    t2 = omp_get_wtime();
    std::cout << "Sequential Time: " << t2 - t1 << std::endl;

    t1 = omp_get_wtime();
    shell_sort_parallel(parallel_a);
    t2 = omp_get_wtime();
    std::cout << "Parallel Time: " << t2 - t1 << std::endl;

    ASSERT_EQ(seq_a, parallel_a);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
