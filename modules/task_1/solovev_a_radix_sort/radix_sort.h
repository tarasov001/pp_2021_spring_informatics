// Copyright 2021 Solovev Aleksandr
#ifndef MODULES_TASK_1_SOLOVEV_A_RADIX_SORT_RADIX_SORT_H_
#define MODULES_TASK_1_SOLOVEV_A_RADIX_SORT_RADIX_SORT_H_
#include <time.h>
#include <stdlib.h>
#include <random>

int generateRandomArray(int* buffer, size_t length, double min, double max);
int MergeArrays(int* buffer1, size_t length1, int *buffer2, size_t length2, int *result);
int SortingCheck(int *buffer, size_t length);
int RadixSortUnsigned(int *buffer, size_t length);
int RadixSort(int* buffer, size_t length);
void BufferClear(int * buffer);

#endif  // MODULES_TASK_1_SOLOVEV_A_RADIX_SORT_RADIX_SORT_H_
