// Copyright 2021 Vlasov Maksim

#include "../../../modules/task_4/vlasov_m_simpson_method/simpson_method.h"

#include <omp.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <utility>

static void sumUp(std::vector<double>* accum, const std::vector<double>& add) {
    assert(accum->size() == add.size());
    for (size_t i = 0; i < accum->size(); i++)
        accum->at(i) += add[i];
}

double SimpsonMethod::sequential(
    const std::function<double(const std::vector<double>&)>& func,
    const std::vector<double>& seg_begin, const std::vector<double>& seg_end,
    int steps_count) {
    if (steps_count <= 0)
        throw std::runtime_error("Steps count must be positive");
    if (seg_begin.empty() || seg_end.empty())
        throw std::runtime_error("No segments");
    if (seg_begin.size() != seg_end.size())
        throw std::runtime_error("Invalid segments");
    size_t dim = seg_begin.size();
    std::vector<double> steps(dim), segments(dim);
    for (size_t i = 0; i < dim; i++) {
        steps[i] = (seg_end[i] - seg_begin[i]) / steps_count;
        segments[i] = seg_end[i] - seg_begin[i];
    }
    std::pair<double, double> sum = std::make_pair(0.0, 0.0);
    std::vector<double> args = seg_begin;
    for (int i = 0; i < steps_count; i += 2) {
        sumUp(&args, steps);
        sum.first += func(args);
        sumUp(&args, steps);
        sum.second += func(args);
    }
    double seg_prod = std::accumulate(segments.begin(), segments.end(), 1.0,
                                      [](double p, double s) { return p * s; });
    return (func(seg_begin) + 4 * sum.first + 2 * sum.second - func(seg_end)) *
           seg_prod / (3.0 * steps_count);
}

double SimpsonMethod::parallel(
    const std::function<double(const std::vector<double>&)>& func,
    std::vector<double> seg_begin, std::vector<double> seg_end,
    int steps_count) {
    if (steps_count <= 0)
        throw std::runtime_error("Steps count must be positive");
    if (seg_begin.empty() || seg_end.empty())
        throw std::runtime_error("No segments");
    if (seg_begin.size() != seg_end.size())
        throw std::runtime_error("Invalid segments");
    double sum = 0;
    int t_count = omp_get_num_procs();
    std::vector<std::unique_ptr<std::thread>> threads(t_count);
    std::mutex lock;
    for (int t_id = 0; t_id < t_count; t_id++) {
        threads[t_id].reset(new std::thread(
            [t_id, t_count, &lock, &sum, &func, steps_count](
                std::vector<double> seg_begin, std::vector<double> seg_end) {
                size_t dim = seg_begin.size();
                size_t i_base = 0;
                for (size_t i = 1; i < dim; i++) {
                    if (seg_end[i] - seg_begin[i] >
                        seg_end[i_base] - seg_begin[i_base])
                        i_base = i;
                }
                double step_size =
                    (seg_end[i_base] - seg_begin[i_base]) / t_count;
                seg_begin[i_base] = seg_begin[i_base] + step_size * t_id;
                seg_end[i_base] = seg_begin[i_base] + step_size;
                double part_sum =
                    sequential(func, seg_begin, seg_end, steps_count / t_count);
                {
                    std::lock_guard<std::mutex> guard(lock);
                    sum += part_sum;
                }
            },
            seg_begin, seg_end));
        threads[t_id]->join();
    }
    return sum;
}
