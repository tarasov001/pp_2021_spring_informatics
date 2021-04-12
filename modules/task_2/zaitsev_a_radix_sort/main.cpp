// Copyright 2021 Zaitsev Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./RadixSortOmp.h"

TEST(Test_Omp, Size_5_Without_Random) {
  int size = 5;
  double* vec = new double[size] {5.21, -8.652,
    26.32, 3.289, -14.842};
  double* tmp = new double[size];
  bool result = false;
  radixSort(vec, tmp, size);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] tmp;
  delete[] vec;
}

TEST(Test_Omp, Size_1000_Random_Pos_And_Neg) {
  int size = 1000;
  double* vec = new double[size];
  vec = createVector(vec, size, -1000.0, 1000.0);
  double* tmp = new double[size];
  bool result = false;
  radixSort(vec, tmp, size);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] tmp;
  delete[] vec;
}

TEST(Test_Omp, Size_1000_Batcher_Seq_Border_20) {
  int size = 1000;
  double* vec = new double[size];
  vec = createVector(vec, size, -1000.0, 1000.0);
  bool result = false;
  oddEvenMergeSortSeq(vec, size, 20);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] vec;
}

TEST(Test_Omp, Size_100_Batcher_Omp_1thr_Border_25) {
  int size = 100;
  int thr = 1;
  double* vec = new double[size];
  vec = createVector(vec, size, -100.0, 100.0);
  bool result = false;
  oddEvenMergeSortOmp(vec, size, 25, thr);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] vec;
}

TEST(Test_Omp, Size_100_Batcher_Omp_4thr_Border_25) {
  int size = 100;
  int thr = 4;
  double* vec = new double[size];
  vec = createVector(vec, size, -1000.0, 1000.0);
  bool result = false;
  oddEvenMergeSortOmp(vec, size, 25, thr);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] vec;
}

TEST(Test_Omp, Size_1000_Batcher_Omp_4thr_Border_60) {
  int size = 1000;
  int thr = 4;
  double* vec = new double[size];
  vec = createVector(vec, size, -1000.0, 1000.0);
  bool result = false;
  oddEvenMergeSortOmp(vec, size, 60, thr);
  result = check(vec, size);
  ASSERT_EQ(true, result);
  delete[] vec;
}

TEST(Test_Omp, Test_Equality_Seq_Par) {
  int size = 100;
  int thr = 5;
  double* v1 = new double[size];
  v1 = createVector(v1, size, -1000.0, 1000.0);
  std::vector<double> v2;
  for (int i = 0; i < size; i++)
    v2.push_back(v1[i]);
  oddEvenMergeSortSeq(v1, size, 20);
  oddEvenMergeSortOmp(v2.data(), size, 20, thr);
  std::vector<double> new_v1;
  for (int i = 0; i < size; i++)
    new_v1.push_back(v1[i]);
  ASSERT_EQ(new_v1, v2);
  delete[] v1;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
