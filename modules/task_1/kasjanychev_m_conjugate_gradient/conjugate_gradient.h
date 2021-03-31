// Copyright 2021 Kasjanychev Mikhail
#ifndef MODULES_TASK_1_KASJANYCHEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
#define MODULES_TASK_1_KASJANYCHEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_

using namespace std;

#include <iostream>
#include <vector>
#include <cassert>

vector<double> multiMtxVec(vector<vector<double> >, vector<double>);
vector<double> subVec(vector<double>, vector<double>);
vector<double> sumVec(vector<double>, vector<double>);
double scalarProduct(vector<double>, vector<double>);
vector<double> multiVec(double, vector<double>);
vector<double> minusVec(vector<double>);
vector<double> calculateRes(vector<vector<double> >, vector<double>);

#endif  // MODULES_TASK_1_KASJANYCHEV_M_CONJUGATE_GRADIENT_CONJUGATE_GRADIENT_H_
