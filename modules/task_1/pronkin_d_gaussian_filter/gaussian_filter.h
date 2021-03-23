// Copyright 2021 Pronkin Dmitry
#ifndef MODULES_TASK_1_PRONKIN_D_GAUSSIAN_FILTER_GAUSSIAN_FILTER_H_
#define MODULES_TASK_1_PRONKIN_D_GAUSSIAN_FILTER_GAUSSIAN_FILTER_H_

#include <vector>
#include <stdexcept>
#include <random>
#include <ctime>
#include <limits>
#include <cmath>

#define M_PI 3.14159265358979323846

const int KERNEL_SIZE = 3;

std::vector<double> getRandomImage(int height, int width);
std::vector<double> getGaussianKernel(double sigma);
std::vector<double> seqGaussianFilter(const std::vector<double>& image, int height, int width, double sigma);

#endif  // MODULES_TASK_1_PRONKIN_D_GAUSSIAN_FILTER_GAUSSIAN_FILTER_H_
