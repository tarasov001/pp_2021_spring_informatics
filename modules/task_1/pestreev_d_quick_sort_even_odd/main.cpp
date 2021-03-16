// Copyright 2021 Pestreev Daniil
#include <gtest/gtest.h>
#include <vector>
#include "./quick_sort_even_odd_merge.h"

TEST(Quick_Sort_Operations, Test_manual_vector) {
    std::vector<int> vec = {-8098, 1009, -160, -1, 179796, 2,
        -1603, 166, -7396, -199, -18348, -15, 659, 7, 82519};
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}
TEST(Quick_Sort_Operations, Test_random_vector_100) {
    std::vector<int> vec = getRandomVector(100);
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}
TEST(Quick_Sort_Operations, Test_random_vector_1000) {
    std::vector<int> vec = getRandomVector(1000);
    //for(int i = 0; i < vec.size(); i++){
    //    std::cout<<vec[i]<<std::endl;
    //}
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}
TEST(Quick_Sort_Operations, Test_random_vector_42211) {
    std::vector<int> vec = getRandomVector(42211);
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}
TEST(Quick_Sort_Operations, Test_random_vector_412211) {
    std::vector<int> vec = getRandomVector(412211);
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}
TEST(Quick_Sort_Operations, Test_random_vector_3412211) {
    std::vector<int> vec = getRandomVector(3412211);
    std::vector<int> vec_V = quickSortV(vec);
    std::vector<int> vec_std = vec; 
    std::sort(vec_std.begin(), vec_std.end());
    ASSERT_EQ(vec_V, vec_std);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
