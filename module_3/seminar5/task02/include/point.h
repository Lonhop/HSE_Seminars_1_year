#ifndef TASK01_POINT_H
#define TASK01_POINT_H

#include <cmath>


class Point {
private:
    double x;
    double y;

public:
    Point(double x = 0.0, double y = 0.0);
    double distanceToOrigin() const;
    double getX() const;
    double getY() const;
};

#endif