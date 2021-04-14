// Copyright 2021 Tkachev Alexey
#include <random>
#include <ctime>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <climits>
#include <utility>
#include <omp.h>
#include "../../../modules/task_1/tkachev_a_graham_pass/graham_pass.h"

std::vector<Point> getRandomizedVector(double from,
                        double up_to, uint32_t count) {
    assert(from < up_to);
    assert(count > 0);
    std::mt19937 random_generator(time(NULL));
    std::uniform_real_distribution<double> real_dist(from, up_to);
    std::vector<Point> randomized_vector(count);

    for (uint32_t i = 0; i < count; i++) {
        randomized_vector[i].x = real_dist(random_generator);
        randomized_vector[i].y = real_dist(random_generator);
    }

    return randomized_vector;
}

void swapPoints(Point* p1, Point* p2) {
    std::swap(p1->x, p2->x);
    std::swap(p1->y, p2->y);
}

Point nextToTopOfStack(std::stack<Point> points) {
    assert(!points.empty());
    const Point tmp = points.top();
    points.pop();
    const Point result = points.top();
    points.push(tmp);
    return result;
}

double angleThreePoints(Point p1, Point p2, Point p3) {
     return (p2.x - p1.x) * (p3.y - p1.y) -
            (p2.y - p1.y) * (p3.x - p1.x);
}

double distanceTwoPoints(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) +
                (p2.y - p1.y) * (p2.y - p1.y));
}

std::vector<Point> sortedByPolarAngle(std::vector<Point> points, uint64_t count_threads = 1) {
    assert(!points.empty());
    if (count_threads > 1) {
        #pragma omp parallel num_threads(count_threads)
        #pragma omp for
        for (uint64_t i = 2; i < points.size(); i++) {
            #pragma omp for
            for (uint64_t j = 2; j < points.size(); j++) {
                double current_angle = angleThreePoints(
                                    points[j-1], points[j], points[0]);
                if (current_angle <= 0) {
                    swapPoints(&points[j-1], &points[j]);
                } else {
                    if (current_angle == 0) {
                        if (distanceTwoPoints(points[j], points[0]) <
                            distanceTwoPoints(points[j-1], points[0])) {
                            swapPoints(&points[j-1], &points[j]);
                        }
                    }
                }
            }
        }
    }
    for (uint64_t i = 2; i < points.size(); i++) {
        for (uint64_t j = 2; j < points.size(); j++) {
            double current_angle = angleThreePoints(
                                points[j-1], points[j], points[0]);
            if (current_angle <= 0) {
                swapPoints(&points[j-1], &points[j]);
            } else {
                if (current_angle == 0) {
                    if (distanceTwoPoints(points[j], points[0]) <
                        distanceTwoPoints(points[j-1], points[0])) {
                        swapPoints(&points[j-1], &points[j]);
                    }
                }
            }
        }
    }
    return points;
}

uint32_t getIndexMinLeftDownPoint(std::vector<Point> points, uint64_t count_threads = 1) {
    assert(!points.empty());
    double min_x = 100000.0, min_y = 100000.0;

    if (count_threads > 1) {
        std::vector<double> min_xs(count_threads, 0.0);
        std::vector<double> min_ys(count_threads, 0.0);
        #pragma omp parallel num_threads(count_threads) firstprivate(min_y, min_x)
        {
            int current_thread_num = omp_get_thread_num();
            #pragma for
            for (uint32_t i = 0; i < points.size(); i++) {
                if (points[i].y < min_y) {
                    min_ys[current_thread_num] = points[i].y;
                }
            }
            #pragma omp single 
            {
                min_y = *std::min(min_ys.begin(), min_ys.end());
            }
            #pragma for
            for (uint32_t i = 0; i < points.size(); i++) {
                if (points[i].y == min_y) {
                    if (points[i].x < min_x) {
                        min_xs[current_thread_num] = points[i].x;
                    }
                }
            }
            #pragma omp single 
            {
                min_x = *std::min(min_xs.begin(), min_xs.end());
            }
        }
    } else {
        for (uint32_t i = 0; i < points.size(); i++) {
            if (points[i].y < min_y) {
                min_y = points[i].y;
            }
        }
        for (uint32_t i = 0; i < points.size(); i++) {
            if (points[i].y == min_y) {
                if (points[i].x < min_x) {
                    min_x = points[i].x;
                }
            }
        }
    } 
    for (uint32_t i = 0; i < points.size(); i++) {
        if (points[i].x == min_x && points[i].y == min_y) {
            return i;
        }
    }
    throw;
}

std::stack<Point> useGrahamAlgorithm(std::vector<Point> points) {

    assert(!points.empty());

    if (points.size() == 3) {
        std::stack<Point> points_stack;
        for (uint32_t i = 0; i < points.size(); i++) {
            points_stack.push(points[i]);
        }
        points_stack.push(points[0]);
        return points_stack;
    } else {
        if (points.size() < 3) {
            std::stack<Point> points_stack;
            for (uint32_t i = 0; i < points.size(); i++) {
                points_stack.push(points[i]);
            }
            return points_stack;
        }
    }

    swapPoints(&points[0],
        &points[getIndexMinLeftDownPoint(points)]);

    points = sortedByPolarAngle(points);
    points.push_back(points[0]);

    std::stack<Point> points_stack;
    points_stack.push(points[0]);
    points_stack.push(points[1]);
    points_stack.push(points[2]);

    for (uint32_t i = 3; i < points.size(); i++) {
        while (angleThreePoints(
            nextToTopOfStack(points_stack),
            points_stack.top(), points[i]) <= 0) {
            if (!points_stack.empty()) {
                points_stack.pop();
            }
        }
        points_stack.push(points[i]);
    }

    return points_stack;
}

std::stack<Point> useGrahamAlgorithmParallel(std::vector<Point> points) {

    assert(!points.empty());

    const uint64_t THREADS_MEMORY_STEP = 1;

        if (points.size() == 3) {
            std::stack<Point> points_stack;
            for (uint32_t i = 0; i < points.size(); i++) {
                points_stack.push(points[i]);
            }
            points_stack.push(points[0]);
            return points_stack;
        } else {
            if (points.size() < 3) {
                std::stack<Point> points_stack;
                for (uint32_t i = 0; i < points.size(); i++) {
                    points_stack.push(points[i]);
                }
                return points_stack;
            }
        }

        #pragma omp parallel shared(points)
        {
            swapPoints(&points[0],
            &points[getIndexMinLeftDownPoint(points)]);

            points = sortedByPolarAngle(points);
            points.push_back(points[0]);

            std::stack<Point> points_stack;
            points_stack.push(points[0]);
            points_stack.push(points[1]);
            points_stack.push(points[2]);

            for (uint32_t i = 3; i < points.size(); i++) {
                while (angleThreePoints(
                    nextToTopOfStack(points_stack),
                    points_stack.top(), points[i]) <= 0) {
                    if (!points_stack.empty()) {
                        points_stack.pop();
                    }
                }
                points_stack.push(points[i]);
            }

            return points_stack;
        }
}
