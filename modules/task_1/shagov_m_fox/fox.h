// Copyright 2021 Shagov Maksim
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