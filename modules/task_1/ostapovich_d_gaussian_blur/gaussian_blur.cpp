// Copyright 2021 Denis Ostapovich
#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <random>
#include "../../../modules/task_1/ostapovich_d_gaussian_blur/gaussian_blur.h"

void applyFilter(std::vector<uint8_t> matrix, int width) {
    std::size_t length = matrix.size();
    if (length == 0 || width <= 0 || length % width != 0) {
        throw std::invalid_argument("Zero or negative argument passed");
    }

    double core[3][3];
    calculateCore(core);
    int height = length / width;
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            uint8_t result = 0;
            for (int m = -1; m <= 1; m++) {
                for (int n = -1; n <= 1; n++) {
                    result += matrix[width * (i + m) + j + n] * core[m + 1][n + 1];
                }
            }
            matrix[width * i + j] = result;
        }
    }
}

void calculateCore(double core[3][3], double deviation) {
    double sum = 0;
    double s = 2.0 * deviation * deviation;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            double res = (std::exp(-(i * i + j * j) / s)) / (M_PI * s);
            core[i + 1][j + 1] = res;
            sum += res;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            core[i][j] /= sum;
        }
    }
}

std::vector<uint8_t> getRandomMatrix(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Zero or negative argument passed");
    }

    const int size = width * height;
    std::random_device device;
    std::mt19937 gen(device());
    std::vector<uint8_t> matrix(size);
    for (int i = 0; i < size; i++) {
        matrix[i] = gen() % 100;
    }

    return matrix;
}
