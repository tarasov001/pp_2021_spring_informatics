// Copyright 2021 Kasjanychev Mikhail
#include "../../../modules/task_1/kasjanychev_m_conjugate_gradient/conjugate_gradient.h"

using namespace std;

vector<double> multiMtxVec(vector<vector<double> > mtx, vector<double> x) {
    assert(mtx.size() > 0 && x.size() > 0);
    assert(mtx.size() % x.size() == 0);
    vector<double> res;
    for (size_t i = 0; i < mtx.size(); ++i) {
        double tmp = 0;
        for (size_t j = 0; j < x.size(); ++j) {
            tmp += mtx[i][j] * x[j];
        }
        res.push_back(tmp);
    }
    return res;
}

vector<double> subVec(vector<double> a, vector<double> b) {
    assert(a.size() == b.size());
    vector<double> res;
    for (size_t i = 0; i < a.size(); i++) {
        double tmp;
        tmp = a[i] - b[i];
        res.push_back(tmp);
    }
    return res;
}

vector<double> sumVec(vector<double> a, vector<double> b) {
    assert(a.size() == b.size());
    vector<double> res;
    for (size_t i = 0; i < a.size(); i++) {
        double tmp;
        tmp = a[i] + b[i];
        res.push_back(tmp);
    }
    return res;
}

double scalarProduct(vector<double> a, vector<double> b) {
    assert(a.size() == b.size());
    double res = 0;
    for (size_t i = 0; i < a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}

vector<double> multiVec(double a, vector<double> x) {
    vector<double> res;
    for (size_t i = 0; i < x.size(); i++) {
        res.push_back(x[i] * a);
    }
    return res;
}

vector<double> minusVec(vector<double> x) {
    vector<double> res;
    for (size_t i = 0; i < x.size(); i++) {
        res.push_back(-x[i]);
    }
    return res;
}

vector<double> calculateRes(vector<vector<double> > mtx, vector<double> b) {
    int n = mtx.size();
    assert(n > 0);
    int m = mtx[0].size();
    vector<double> x0;
    vector<double> r0;
    vector<double> z0 = minusVec(b);
    for (int i = 0; i < m; i++) {
        x0.push_back(0);
    }
    r0 = subVec(b, multiMtxVec(mtx, x0));
    z0 = r0;
    int i = 0;
    do {
        i++;
        double alpha = (scalarProduct(r0, r0) / (scalarProduct(multiMtxVec(mtx, z0), z0)));
        vector<double> x = sumVec(x0, multiVec(alpha, z0));
        vector<double> r = subVec(r0, multiVec(alpha, multiMtxVec(mtx, z0)));
        double beta = scalarProduct(r, r) / scalarProduct(r0, r0);
        vector<double> z = sumVec(r, multiVec(beta, z0));
        x0 = x;
        r0 = r;
        z0 = z;
    } while (i < n);
    return x0;
}
