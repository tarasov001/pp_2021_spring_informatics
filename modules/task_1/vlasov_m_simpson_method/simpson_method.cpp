// Copyright 2021 Vlasov Maksim

#include "../../../modules/task_1/vlasov_m_simpson_method/simpson_method.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>

static void sumUp(std::vector<double>* accum, const std::vector<double>& add) {
    assert(accum->size() == add.size());
    for (size_t i = 0; i < accum->size(); i++)
        accum->at(i) += add[i];
}

double SimpsonMethod::integrate(
    const std::function<double(const std::vector<double>&)>& func,
    const std::vector<double>& seg_begin, const std::vector<double>& seg_end,
    size_t steps) {
    if (seg_begin.empty() || seg_end.empty())
        throw std::runtime_error("No segments");
    if (seg_begin.size() != seg_end.size())
        throw std::runtime_error("Invalid segments");
    size_t dim = seg_begin.size();
    std::vector<double> step(dim), h(dim);
    for (size_t i = 0; i < dim; i++) {
        step[i] = (seg_end[i] - seg_begin[i]) / static_cast<int>(steps);
        h[i] = seg_end[i] - seg_begin[i];
    }
    double odds = 0;
    double evens = 0;
    std::vector<double> args = seg_begin;
    for (size_t i = 0; i < steps; i += 2) {
        sumUp(&args, step);
        odds += func(args);
        sumUp(&args, step);
        evens += func(args);
    }
    double h_total = std::accumulate(h.begin(), h.end(), 1.0,
                                     [](double a, double b) { return a * b; });
    return (h_total / steps) *
           (func(seg_begin) + 4 * odds + 2 * evens - func(seg_end)) / 3.0;
}
