// Copyright 2021 Solovev Aleksandr
#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include "../../../modules/task_1/solovev_a_radix_sort/radix_sort.h"


TEST(Senquential, Test_Only_Positive) {
    const int length = 10000;
    int status = 0;
    int *buffer1 = nullptr;
    if (length > 0) {
        buffer1 = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer1, length, 0.0, 1000.0);

    status = RadixSort(buffer1, length);

    status = SortingCheck(buffer1, length);
    BufferClear(buffer1);

    ASSERT_EQ(status, 0);
}


TEST(Senquential, Test_Only_Negative) {
    const int length = 10000;
    int status = 0;
    int *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer, length, -1000.0, 0.0);

    status = RadixSort(buffer, length);
    status = SortingCheck(buffer, length);
    BufferClear(buffer);

    ASSERT_EQ(status, 0);
}

TEST(Senquential, Test_Small_length) {
    const int length = 100;
    int status = 0;
    int *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer, length, -5000.0, 5000.0);

    status = RadixSort(buffer, length);
    status = SortingCheck(buffer, length);
    BufferClear(buffer);

    ASSERT_EQ(status, 0);
}

TEST(Senquential, Test_Medium_Length) {
    const int length = 10000;
    int status = 0;
    int *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer, length, -5000.0, 5000.0);

    status = RadixSort(buffer, length);
    status = SortingCheck(buffer, length);
    BufferClear(buffer);

    ASSERT_EQ(status, 0);
}

TEST(Senquential, Test_Large_Length) {
    const int length = 100000;
    int status = 0;
    int *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer, length, -3000.0, 3000.0);

    status = RadixSort(buffer, length);
    status = SortingCheck(buffer, length);
    BufferClear(buffer);

    ASSERT_EQ(status, 0);
}

TEST(Senquential, Test_Very_Large_Length) {
    const int length = 120000;
    int status = 0;
    int *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<int*>(malloc(sizeof(int) * length));
    } else {
        status = -1;
    }

    status = generateRandomArray(buffer, length, -5000.0, 5000.0);

    status = RadixSort(buffer, length);
    status = SortingCheck(buffer, length);
    BufferClear(buffer);

    ASSERT_EQ(status, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
