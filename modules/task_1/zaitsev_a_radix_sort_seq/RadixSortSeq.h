// Copyright 2021 Zaitsev Andrey
#ifndef MODULES_TASK_1_ZAITSEV_A_RADIX_SORT_SEQ_RADIXSORTSEQ_H_
#define MODULES_TASK_1_ZAITSEV_A_RADIX_SORT_SEQ_RADIXSORTSEQ_H_

#include <vector>

void merge(double *vec, double *tmp, int center, int size, int odd_even);
void oddEvenMergeSort(double *vec, double *tmp, int size, int border);
void radixSort(double *vec, double *tmp, int size);
std::vector<double> createVector(int size, double a, double b);

#endif  // MODULES_TASK_1_ZAITSEV_A_RADIX_SORT_SEQ_RADIXSORTSEQ_H_