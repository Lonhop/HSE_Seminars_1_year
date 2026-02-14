#include "point.h"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distanceToOrigin() const {
    return std::sqrt(x * x + y * y);
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}