// Copyright 2021 Chirkov Roman
#ifndef MODULES_TASK_1_CHIRKOV_R_JARVIS_MARCH_JARVIS_MARCH_H_
#define MODULES_TASK_1_CHIRKOV_R_JARVIS_MARCH_JARVIS_MARCH_H_

#include <vector>

class Point {
 private:
  double x;
  double y;

 public:
  Point();
  Point(double _x, double _y);

  double getX();
  double getY();
  void setX(double _x);
  void setY(double y);
  bool isCloserToA(Point A, Point B);
  friend bool operator<(Point A, Point B);
  friend bool operator==(Point A, Point B);
};

std::vector<Point> makePointsArray(int amount);
double rotate(Point A, Point B, Point C);
std::vector<int> ParallelJarvis(std::vector<Point> points);

#endif  // MODULES_TASK_1_CHIRKOV_R_JARVIS_MARCH_JARVIS_MARCH_H_
