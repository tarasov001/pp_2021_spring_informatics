// Copyright 2021 Napylov Evgenii
#ifndef MODULES_TASK_1_NAPYLOV_E_CONTRAST_CONTRAST_H_
#define MODULES_TASK_1_NAPYLOV_E_CONTRAST_CONTRAST_H_

#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <ctime>
#include <algorithm>

typedef std::vector<unsigned char> VecImage;

void print_vec(const VecImage& vec);

VecImage RandomVector(int size);

VecImage add_contrast(VecImage image, unsigned char down = 0,
                                      unsigned char up = 255);

#endif  // MODULES_TASK_1_NAPYLOV_E_CONTRAST_CONTRAST_H_
