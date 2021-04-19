// Copyright 2021 Streltsova Yana
#ifndef MODULES_TASK_2_STRELTSOVA_Y_SHELL_SORT_SHELL_SORT_H_
#define MODULES_TASK_2_STRELTSOVA_Y_SHELL_SORT_SHELL_SORT_H_

#include <omp.h>

#include <utility>
#include <vector>

std::vector<int> getRandomVectorInt(int  sz);

std::vector<double> getRandomVectorDouble(int  sz);

template< typename T >
void shell_sort_sequential(std::vector<T>* vec) {
    int d = 4;
    while (d > 0) {
        for (int i = 0; i < vec.size(); i++) {
            for (int j = i + d; j < vec.size(); j += d) {
                if (vec[i] > vec[j])
                    std::swap(vec[i], vec[j]);
            }
        }
        d /= 2;
    }
}

template< typename T >
void shell_sort_parallel(std::vector<T>* vec) {
    if (vec.size() < 1000)
        return shell_sort_sequential(vec);
    int d = 4;
    while (d > 0) {
        omp_set_num_threads(d);
#pragma omp parallel
        {
        int tid = omp_get_thread_num();
        for (int i = tid; i < vec.size(); i += d)
            for (int j = i + d; j < vec.size(); j += d) {
                if (vec[i] > vec[j])
                    std::swap(vec[i], vec[j]);
            }
        }
        d /= 2;
    }
}

#endif  // MODULES_TASK_2_STRELTSOVA_Y_SHELL_SORT_SHELL_SORT_H_
