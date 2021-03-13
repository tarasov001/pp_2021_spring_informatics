// Copyright 2021 Vlasov Maksim

#include "../../../modules/task_1/vlasov_m_simpson_method/simpson_method.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>

using namespace SimpsonMethod;

static void sumUp(std::vector<double>* accum, const std::vector<double>& add) {
    assert(accum->size() == add.size());
    for (size_t i = 0; i < accum->size(); i++)
        accum->at(i) += add[i];
}

double
integrate(int steps, const std::vector<double>& seg_begin,
          const std::vector<double>& seg_end,
          const std::function<double(const std::vector<double>&)>& func) {
    if (seg_begin.size() != seg_end.size())
        throw std::runtime_error("Unequal sizes");
    size_t dim = seg_begin.size();
    std::vector<double> step(dim);
    for (size_t i = 0; i < dim; i++)
        step[i] = (seg_end[i] - seg_begin[i]) / steps;
    double odds = 0;
    double evens = 0;
    std::vector<double> args = seg_begin;
    for (size_t i = 0; i < steps; i += 2) {
        sumUp(&args, step);
        odds += func(args);
        sumUp(&args, step);
        evens += func(args);
    }
    double h_total = std::accumulate(step.begin(), step.end(), 1,
                                     [](double a, double b) { return a * b; });
    return h_total * (func(seg_begin) + 4 * odds + 2 * evens - func(seg_end));
}
