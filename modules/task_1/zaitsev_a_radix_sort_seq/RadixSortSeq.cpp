// Copyright 2021 Zaitsev Andrey
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../../../modules/task_1/zaitsev_a_radix_sort_seq/RadixSortSeq.h"

std::vector<double> createVector(int size, double a, double b) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::uniform_real_distribution<double> distr(a, b);
  std::vector<double> vec(size);
  for (int i = 0; i < size; i++) {
    vec[i] = distr(gen);
  }
  return vec;
}

void radixSort(double *vec, double *tmp, int size) {
  double* swap = nullptr;
  double* arr = new double[size];
  for (int i = 0; i < size; i++)
    arr[i] = vec[i];
  for (int i = 0; i < 7; i++) {
    unsigned char* arr2 = (unsigned char*)arr;
    int cnt[256] = { 0 };
    int res = 0;
    for (int j = 0; j < size; j++)
      cnt[arr2[8 * j + i]]++;
    for (int j = 0; j < 256; j++) {
      int tmp_ = cnt[j];
      cnt[j] = res;
      res += tmp_;
    }
    for (int j = 0; j < size; j++) {
      int ind = 8 * j + i;
      tmp[cnt[arr2[ind]]] = arr[j];
      cnt[arr2[ind]]++;
    }

    swap = arr;
    arr = tmp;
    tmp = swap;
  }

  unsigned char* arr2 = (unsigned char*)arr;
  int cnt[256] = { 0 };
  int shift[256] = { 0 };
  for (int i = 0; i < size; i++)
    cnt[arr2[8 * i + 7]]++;
  shift[255] = cnt[255] - 1;
  for (int i = 254; i >= 128; i--)
    shift[i] = shift[i + 1] + cnt[i];
  shift[0] = shift[128] + 1;
  for (int i = 1; i < 128; i++)
    shift[i] = shift[i - 1] + cnt[i - 1];
  for (int i = 0; i < size; i++) {
    if (arr2[8 * i + 7] < 128)
      vec[shift[arr2[8 * i + 7]]++] = arr[i];
    else
      vec[shift[arr2[8 * i + 7]]--] = arr[i];
  }
  delete[] arr;
}

void merge(double *vec, double *tmp, int center, int size, int odd_even) {
  for (int i = odd_even; i < center; i += 2)
    tmp[i] = vec[i];
  double *inp2 = vec + center;
  int par1 = odd_even;
  int par2 = odd_even;
  int ind = odd_even;
  while ((par1 < center) && (par2 < size)) {
    if (tmp[par1] > inp2[par2]) {
      vec[ind] = inp2[par2];
      par2 += 2;
    } else {
      vec[ind] = tmp[par1];
      par1 += 2;
    }
    ind += 2;
  }
  if (par1 != center) {
    for (int j = par1; j < center; j += 2, ind += 2)
      vec[ind] = tmp[j];
  } else {
    for (int j = par2; j < size; j += 2, ind += 2)
      vec[ind] = inp2[j];
  }
}

void oddEvenMergeSort(double *vec, double *tmp, int size, int border) {
  if (size <= border) {
    radixSort(vec, tmp, size);
  } else {
    int center = size / 2 + (size / 2) % 2;
    oddEvenMergeSort(vec, tmp, center, border);
    oddEvenMergeSort(vec + center, tmp + center, size - center, border);
    merge(vec, tmp, center, size - center, 0);
    merge(vec, tmp, center, size - center, 1);
    for (int i = 1; i < (size + 1) / 2; i++) {
      if (vec[2 * i] < vec[2 * i - 1]) {
        double tmp = vec[2 * i - 1];
        vec[2 * i - 1] = vec[2 * i];
        vec[2 * i] = tmp;
      }
    }
  }
}
