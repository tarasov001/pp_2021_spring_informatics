// Copyright 2021 Shagov Maksim
#ifndef MODULES_TASK_1_SHAGOV_M_FOX_FOX_H_
#define MODULES_TASK_1_SHAGOV_M_FOX_FOX_H_
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>
#include <limits>

typedef  std::vector<double> Matrix;

bool isEqual(double x, double y);
bool isEqualMatrix(Matrix A, Matrix B);

Matrix createRandomMatrix(size_t size);
Matrix sequentialMatrixmultiplication(std::vector<double> A, std::vector<double> B, size_t BlockSize);
#endif  // MODULES_TASK_1_SHAGOV_M_FOX_FOX_H_
