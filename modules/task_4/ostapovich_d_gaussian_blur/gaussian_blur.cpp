// Copyright 2021 Denis Ostapovich
#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <random>
#include "../../../modules/task_4/ostapovich_d_gaussian_blur/gaussian_blur.h"
#include "../../../3rdparty/unapproved/unapproved.h"
#include <iostream>

std::vector<uint8_t> filter(const std::vector<uint8_t>& matrix, int width, int coreSize) {
    std::size_t length = matrix.size();

    if (length == 0 || width <= 0 || length % width != 0 || coreSize < 3 || coreSize % 2 == 0) {
        throw std::invalid_argument("Zero or negative argument passed");
    }

    int radius = coreSize / 2;
    auto core = calculateCore(coreSize);

    std::cout << "Core:\n";
    for (int i = 0; i < core.size(); i++) {
        std::cout << +core[i] << " ";
        if (i % width == width - 1) {
            std::cout << std::endl;
        }
    }

    int height = length / width;
    std::vector<uint8_t> filtered(matrix);

    std::cout << "Filtered:\n";
    for (int i = 0; i < filtered.size(); i++) {
        std::cout << +filtered[i] << " ";
        if (i % width == width - 1) {
            std::cout << std::endl;
        }
    }

    for (int i = radius; i < height - radius; i++) {
        for (int j = radius; j < width - radius; j++) {
            uint8_t result = 0;
            for (int m = -radius; m <= radius; m++) {
                for (int n = -radius; n <= radius; n++) {
                    result += matrix[width * (i + m) + j + n] * core[coreSize * (m + radius) + n + radius];
                }
            }
            filtered[width * i + j] = result;
        }
    }

    return filtered;
}

std::vector<uint8_t> filterParallel(const std::vector<uint8_t>& matrix, int width, int coreSize) {
    const std::size_t length = matrix.size();
    //const int nthreads = std::thread::hardware_concurrency();
    const int nthreads = 2;

    if (length == 0 || width <= 0 || length % width != 0 || coreSize < 3 || coreSize % 2 == 0) {
        throw std::invalid_argument("Zero or negative argument passed");
    }

    const int radius = coreSize / 2;
    const std::vector<double> core = calculateCore(coreSize);

    std::cout << "Core:\n";
    for (int i = 0; i < core.size(); i++) {
        std::cout << +core[i] << " ";
        if (i % width == width - 1) {
            std::cout << std::endl;
        }
    }

    const int height = length / width;
    std::vector<uint8_t> filtered(matrix);

    std::cout << "Filtered:\n";
    for (int i = 0; i < filtered.size(); i++) {
        std::cout << +filtered[i] << " ";
        if (i % width == width - 1) {
            std::cout << std::endl;
        }
    }

    const int rowIterations = height - 2 * radius;
    const int columnIterations = width - 2 * radius;

    const int rowDelta = rowIterations / nthreads;
    const int rowRemainder = rowIterations % nthreads;
    const int columnDelta = columnIterations / nthreads;
    const int columnRemainder = columnIterations % nthreads;

    if (rowDelta == 0 && columnDelta == 0) {
        return filter(matrix, width, coreSize);
    }

    std::thread* threads = new std::thread[nthreads];

    for (int i = 0; i < nthreads; i++) {

        /*int startRow = radius + i * rowDelta;
        int endRow = i == nthreads - 1 ? startRow + rowDelta + rowRemainder - 1: startRow + rowDelta - 1;
        int startColumn = radius + i * columnDelta;
        int endColumn = i == nthreads - 1 ?
            startColumn + columnDelta + rowRemainder - 1 : startColumn + columnDelta - 1;*/

        /*threads[i] = std::thread([&](int startRow, int endRow,
            int startColumn, int endColumn) {
                for (int j = startRow; j <= endRow; j++) {
                    for (int k = startColumn; k <= endColumn; k++) {
                    uint8_t result = 0;
                    for (int m = -radius; m <= radius; m++) {
                        for (int n = -radius; n <= radius; n++) {
                            result += matrix[width * (j + m) + k + n] * core[coreSize * (m + radius) + n + radius];
                        }
                    }

                    filtered[width * j + k] = result;
                }
            }
            }, startRow, endRow,
                startColumn, endColumn);*/
        threads[i] = std::thread([&](int rowDelta, int rowRemainder,
            int columnDelta, int columnRemainder) {
                for (int j = radius; j < height - radius; j++) {
                    for (int k = radius; k < width - radius; k++) {
                        uint8_t result = 0;
                        int a = k - radius >= columnDelta * (nthreads - 1) ? nthreads - 1 : (k - radius) / columnDelta;
                        int b = j - radius >= rowDelta * (nthreads - 1) ? nthreads - 1 : (j - radius) / rowDelta;
                        if ((a + b)%nthreads == i) {
                            for (int m = -radius; m <= radius; m++) {
                                for (int n = -radius; n <= radius; n++) {
                                    result += matrix[width * (j + m) + k + n] * core[coreSize * (m + radius) + n + radius];
                                }
                            }
                        }

                        filtered[width * j + k] = result;
                    }
                }
            }, rowDelta, rowRemainder,
            columnDelta, columnRemainder);
    }
    
    for (int i = 0; i < nthreads; i++) {
        threads[i].join();
    }

    delete[]threads;

    return filtered;
}

std::vector<double> calculateCore(int size, double deviation) {
    if (size < 3) {
        throw std::out_of_range("Size must be greater or equal to 3");
    }
    if (size % 2 == 0) {
        throw std::invalid_argument("Size must be an odd number");
    }
    double sum = 0;
    double s = 2.0 * deviation * deviation;
    int radius = size / 2;
    std::vector<double> core(size * size);

    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            double res = (std::exp(-(i * i + j * j) / s)) / (M_PI * s);
            core[size * (i + radius) + j + radius] = res;
            sum += res;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            core[size * i + j] /= sum;
        }
    }

    return core;
}

std::vector<uint8_t> getRandomMatrix(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Zero or negative arguments passed");
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
