// Copyright 2021 Denis Ostapovich
#ifndef MODULES_TASK_4_OSTAPOVICH_D_GAUSSIAN_BLUR_GAUSSIAN_BLUR_H_
#define MODULES_TASK_4_OSTAPOVICH_D_GAUSSIAN_BLUR_GAUSSIAN_BLUR_H_

#include<vector>
#include<cstdint>

using vec = std::vector<uint8_t>;

struct Chunk {
    std::pair<int, int> topLeftCorner{};
    std::pair<int, int> bottomRightCorner{};
};

std::vector<double> calculateCore(int size, double deviation = 1.0);
vec getRandomMatrix(int width, int height);
vec filter(const vec& matrix, int width, int coreSize = 3);
vec filterParallel(const vec& matrix, int width, int coreSize = 3);
std::vector<std::vector<Chunk>> performScheduling(int width, int height, int coreRadius, int numThreads);

#endif  // MODULES_TASK_4_OSTAPOVICH_D_GAUSSIAN_BLUR_GAUSSIAN_BLUR_H_