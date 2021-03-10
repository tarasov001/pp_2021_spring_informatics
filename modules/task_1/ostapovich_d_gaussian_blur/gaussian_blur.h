// Copyright 2021 Denis Ostapovich
#ifndef MODULES_TASK_1_OSTAPOVICH_D_GAUSSIAN_BLUR_H_
#define MODULES_TASK_1_OSTAPOVICH_D_GAUSSIAN_BLUR_H_

#include<vector>
#include<cstdint>

void applyFilter(std::vector<uint8_t> matrix, int width);
void calculateCore(double core[3][3], double deviation = 1.0);
std::vector<uint8_t> getRandomMatrix(int width, int height);

#endif
