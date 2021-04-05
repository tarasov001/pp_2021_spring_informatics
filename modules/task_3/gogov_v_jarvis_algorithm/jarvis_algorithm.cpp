// Copyright 2021 Gogov Vladislav
#include <random>
#include "../../../modules/task_3/gogov_v_jarvis_algorithm/jarivs_algorithm.h"

int rotate(const Point& A, const Point& B, const Point& C) {
    int64_t temp = (C.first - A.first) * (B.second - A.second) -
                   (C.second - A.second) * (B.first - A.first);
    if (temp > 0)
        return 1;
    else if (temp < 0)
        return -1;
    else
        return 0;
}

std::vector<Point> getRandomPoints(size_t size) {
    if (size <= 0)
        throw("The size cannot be zero");
    std::random_device device;
    std::mt19937 gen(device());
    std::vector<Point> points(size);
    for (size_t i = 0; i < size; i++) {
        size_t x = static_cast<size_t>(gen() % 1000ull);
        size_t y = static_cast<size_t>(gen() % 1000ull);
        points[i] = Point(x, y);
    }
    return points;
}

Point searchBottomLeft(const std::vector<Point>& points) {
    Point point_bottom_left = points[0];
    for (size_t i = 1; i < points.size(); i++)
        if (points[i] < point_bottom_left)
            point_bottom_left = points[i];
    return point_bottom_left;
}

bool checkPointsDistances(const Point& current, const Point& next,
                          const Point& temp) {
    size_t dist_nefirstt_current =
        (next.first - current.first) * (next.first - current.first) +
        (next.second - current.second) * (next.second - current.second);
    size_t dist_temp_current =
        (temp.first - current.first) * (temp.first - current.first) +
        (temp.second - current.second) * (temp.second - current.second);
    if (dist_nefirstt_current < dist_temp_current)
        return true;
    return false;
}

std::vector<Point> jarvisAlgorithmSeq(const std::vector<Point>& points) {
    size_t count_points = points.size();
    if (count_points == 0)
        throw("It is impossible to construct a convefirst hull");
    if (count_points < 2)
        return points;
    Point base = searchBottomLeft(points);
    std::vector<Point> convex_hull;
    convex_hull.push_back(base);
    Point current = base;
    Point next;
    do {
        next = current == points[0] ? points[1] : points[0];

        for (size_t i = 0; i < count_points; i++) {
            int temp = rotate(current, next, points[i]);
            if (temp > 0) {
                next = points[i];
            } else if (temp == 0) {
                if (checkPointsDistances(current, next, points[i])) {
                    next = points[i];
                }
            }
        }
        current = next;
        convex_hull.push_back(next);
    } while (current != base);
    convex_hull.pop_back();
    return convex_hull;
}

class FirstPoint {
    const std::vector<Point>& points;
    Point base;

 public:
    FirstPoint(const std::vector<Point>& points_, Point base_) : points(points_), base(base_) {
    }

    FirstPoint(const FirstPoint& r, tbb::split) : points(r.points), base(r.base) {
    }

    void operator()(const tbb::blocked_range<size_t>& r) {
        auto begin = r.begin(), end = r.end();
        for (auto i = begin; i != end; i++) {
            if (points[i] < base)
                base = points[i];
        }
    }

    void join(const FirstPoint& r) {
        if (r.base < base)
            base = r.base;
    }

    Point getBase() {
        return base;
    }
};

class NextPoint {
    Point next;
    const std::vector<Point>& points;
    Point last_point_hull;

 public:
    NextPoint(const std::vector<Point>& points_, Point next_, Point last_point_hull_)
        : next(next_), points(points_), last_point_hull(last_point_hull_) {
    }

    NextPoint(const NextPoint& r, tbb::split)
        : next(r.next), points(r.points), last_point_hull(r.last_point_hull) {
    }

    void operator()(const tbb::blocked_range<size_t>& r) {
        auto begin = r.begin(), end = r.end();
        for (auto i = begin; i != end; i++) {
            int temp = rotate(last_point_hull, next, points[i]);
            if (temp > 0) {
                next = points[i];
            } else if (temp == 0) {
                if (checkPointsDistances(last_point_hull, next, points[i]))
                    next = points[i];
            }
        }
    }

    void join(const NextPoint& r) {
        int temp = rotate(r.last_point_hull, next, r.next);
        if (temp > 0) {
            next = r.next;
        } else if (temp == 0) {
            if (checkPointsDistances(r.last_point_hull, next, r.next))
                next = r.next;
        }
    }

    Point getNext() {
        return next;
    }
};

std::vector<Point> jarvisAlgorithmTbb(const std::vector<Point>& points) {
    int count_points = static_cast<int>(points.size());
    if (count_points == 0)
        throw("It is impossible to construct a convefirst hull");
    if (count_points < 2)
        return points;

    FirstPoint base_point(points, points[0]);
    tbb::parallel_reduce(tbb::blocked_range<size_t>(1, count_points), base_point);
    Point base = base_point.getBase();

    std::vector<Point> convex_hull;
    convex_hull.push_back(base);
    Point current = base;
    Point next;
    do {
        next = current == points[0] ? points[1] : points[0];
        NextPoint next_point(points, next, current);
        tbb::parallel_reduce(tbb::blocked_range<size_t>(0, count_points), next_point);
        current = next_point.getNext();
        next = current;
        convex_hull.push_back(next);
    } while (current != base);
    convex_hull.pop_back();
    return convex_hull;
}
