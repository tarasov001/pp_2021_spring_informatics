// Copyright 2021 Rustamov Azer

#ifndef MODULES_TASK_1_RUSTAMOV_A_HISTOGRAM_STRETCH_HISTOGRAM_STRETCH_H
#define MODULES_TASK_1_RUSTAMOV_A_HISTOGRAM_STRETCH_HISTOGRAM_STRETCH_H
#include <vector>

using Matrix = std::vector<int>;

Matrix generate_random_image(int w, int h, int bit = 8, int min_y = 50, int max_y = 150);
Matrix make_histogram(const Matrix& image, int w, int h, int bit = 8);
Matrix stretch_histogram(const Matrix& histogram, int w, int h, int& a, int& b, int bit = 8);
Matrix increase_contrast(const Matrix& image, Matrix, const Matrix& histogram, int w, int h, int bit = 8);



#endif  // MODULES_TASK_1_RUSTAMOV_A_HISTOGRAM_STRETCH_HISTOGRAM_STRETCH_H
