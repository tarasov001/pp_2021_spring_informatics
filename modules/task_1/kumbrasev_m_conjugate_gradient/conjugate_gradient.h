// Copyright 2021 Kumbrasev Mark
#ifndef MODULES_TASK_1_KUMBRASEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
#define MODULES_TASK_1_KUMBRASEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

vector<double> linVec(double a, const vector<double> &v1, double b, const vector<double> &v2);
double innerVec(const vector<double> &v1, const vector<double> &v2);
vector<double> mMultv(const vector<vector<double>> &M, const vector<double> &V);
double vecNorm(const vector<double> &V);
vector<double> ConjugateGradient(const vector<vector<double>> &M, const vector<double> &B);

#endif  // MODULES_TASK_1_KUMBRASEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
