// Copyright 2021 Pronkin Dmitry
#ifndef MODULES_TASK_1_PRONKIN_DMITRY_GAUSSIAN_FILTER_H_
#define MODULES_TASK_1_PRONKIN_DMITRY_GAUSSIAN_FILTER_H_

#include <vector>
#include <stdexcept>
#include <random>
#include <ctime>
#include <limits>

const int KERNEL_SIZE = 3;
const unsigned int KERNEL_NORM = 4;
const int KERNEL[] = {1, 2, 1};

std::vector<double> getRandomImage(int height, int width);
std::vector<double> seqGaussianFilter(const std::vector<double>& image, int height, int width);

#endif  // MODULES_TASK_1_PRONKIN_DMITRY_GAUSSIAN_FILTER_H_
