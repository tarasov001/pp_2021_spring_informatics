// Copyright 2021 Zaitsev Andrey
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./RadixSortSeq.h"

TEST(Test_Seq, Size_5_Without_Random) {
  int size = 5;
  std::vector<double> vec = { 4.33, -6.541, 16.84, 2.662, -12.544 };
  double* tmp = new double[size];
  std::vector<double> vec2(vec);
  radixSort(vec.data(), tmp, size);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Size_1000_Random_Positive) {
  int size = 1000;
  std::vector<double> vec = createVector(size, 100.0, 1000.0);
  double* tmp = new double[size];
  std::vector<double> vec2(vec);
  radixSort(vec.data(), tmp, size);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Size_1000_Random_Negative) {
  int size = 1000;
  std::vector<double> vec = createVector(size, -800.0, 0.0);
  double* tmp = new double[size];
  std::vector<double> vec2(vec);
  radixSort(vec.data(), tmp, size);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Size_1000_Random_Pos_And_Neg) {
  int size = 1000;
  std::vector<double> vec = createVector(size, -500.0, 500.0);
  double* tmp = new double[size];
  std::vector<double> vec2(vec);
  radixSort(vec.data(), tmp, size);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Exact_Answer) {
  int size = 7;
  std::vector<double> vec = {5.32, 8.25, 3.463, 43.733, 120.632, 75.86, 53.41};
  std::vector<double> answer =
  {3.463, 5.32, 8.25, 43.733, 53.41, 75.86, 120.632};
  double* tmp = new double[size];
  radixSort(vec.data(), tmp, size);
  for (int i = 0; i < size; i++)
    ASSERT_NEAR(vec[i], answer[i], 0.01);
  delete[] tmp;
}

TEST(Test_Seq, Size_100_Batcher) {
  int size = 100;
  double* tmp = new double[size];
  std::vector<double> vec = createVector(size, 0.0, 1000.0);
  std::vector<double> vec2(vec);
  oddEvenMergeSort(vec.data(), tmp, size, 6);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Size_1000_Batcher_Border_20) {
  int size = 1000;
  double* tmp = new double[size];
  std::vector<double> vec = createVector(size, -1000.0, 1000.0);
  std::vector<double> vec2(vec);
  oddEvenMergeSort(vec.data(), tmp, size, 20);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

TEST(Test_Seq, Size_1000_Batcher_Border_1000) {
  int size = 1000;
  double* tmp = new double[size];
  std::vector<double> vec = createVector(size, -1000.0, 1000.0);
  std::vector<double> vec2(vec);
  oddEvenMergeSort(vec.data(), tmp, size, 1000);
  std::sort(vec2.begin(), vec2.end());
  ASSERT_EQ(vec2, vec);
  delete[] tmp;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
