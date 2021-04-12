// Copyright 2021 Chirkov Roman
#include "../../../modules/task_2/chirkov_r_jarvis_march/jarvis_march.h"

#include <omp.h>

#include <ctime>
#include <iostream>
#include <random>
#include <vector>

Point::Point() {
  x = 0;
  y = 0;
}
Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
}
double Point::getX() { return x; }
double Point::getY() { return y; }
void Point::setX(double _x) { x = _x; }
void Point::setY(double _y) { y = _y; }

bool Point::isCloserToA(Point A, Point B) {
  return (A.x <= x && x <= B.x && A.y <= y && y <= B.y);
}
bool operator<(Point A, Point B) {
  if (A.y < B.y)
    return true;
  else
    return ((A.y == B.y) && (A.x < B.x));
}
bool operator==(Point A, Point B) { return (A.x == B.x && A.y == B.y); }

std::vector<Point> makePointsArray(int amount) {
  if (amount <= 0) {
    throw "Wrong amount of points!";
  }
  std::vector<Point> points;
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));

#pragma omp parallel
  {
    std::vector<Point> loc_points;
#pragma omp for
    for (int i = 0; i < amount; i++) {
      loc_points.push_back(Point(gen() % 1000, gen() % 1000));
    }
#pragma omp critical
    points.insert(points.end(), loc_points.begin(), loc_points.end());
  }
  return points;
}

double rotate(Point A, Point B, Point C) {
  return (B.getX() - A.getX()) * (C.getY() - B.getY()) -
         (B.getY() - A.getY()) * (C.getX() - B.getX());
}

std::vector<int> ParallelJarvis(std::vector<Point> points) {
  int N = points.size();
  switch (N) {
    case 0:
      throw "wrong amount of points!";
    case 1:
      return std::vector<int>(2, 0);
  }

  std::cout << "Checked" << std::endl;
  /*
    int index = 0;
    Point startPoint = points[0];
  #pragma omp parallel
    {
      Point loc_startPoint = startPoint;
      int loc_index = index;
  #pragma omp for schedule(static)
      for (int i = 1; i < N; i++) {
        if (points[i] < loc_startPoint) {
          loc_startPoint = points[i];
          loc_index = i;
        }
      }
  #pragma omp critical
      {
        if (loc_startPoint < startPoint) {
          startPoint = loc_startPoint;
          index = loc_index;
        }
      }
    }
  */
  int index = 0;
  Point startPoint = points[0];
  for (int i = 1; i < N; i++) {
    Point next = points[i];
    if (startPoint == next) {
      continue;
    }
    if ((next.getY() < startPoint.getY()) ||
        ((startPoint.getY() == next.getY()) &&
         (next.getX() < startPoint.getX()))) {
      startPoint = next;
      index = i;
    }
  }
  std::cout << "Point found" << std::endl;

  std::vector<int> hull;
  hull.push_back(index);
  int cur = index;
  do {
    int next = (cur + 1) % N;
    // int next = cur == 0 ? 1 : 0;
    std::cout << "do" << std::endl;
    for (int i = 0; i < N; i++) {
      std::cout << "for" << std::endl;
      double pos = rotate(points[cur], points[next], points[i]);
      if (pos < 0) {
        next = i;
      } else if (pos == 0) {
        if (points[next].isCloserToA(points[cur], points[i])) {
          next = i;
        }
      }
    }
    cur = next;
    std::cout << "cur=" << cur << std::endl;
    std::cout << "index=" << index << std::endl;
    hull.push_back(next);
  } while (cur != index);
  std::cout << "before return" << std::endl;
  return hull;
}
