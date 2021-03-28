// Copyright 2021 Streltsova Yana

#include <random>
#include <ctime>

#include "./Shell_sort.h"

std::vector<int> getRandomVector(int size) {
    std::mt19937 gen(time(0));
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) { vec[i] = gen() % 100; }
    return vec;
}
