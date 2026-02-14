#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "point.h"

int main() {
    std::vector<Point> points = {
        Point(3.0, 4.0),
        Point(-1.0, 1.0),
        Point(0.0, 2.0),
        Point(5.0, 0.0),
        Point(1.5, 1.5),
        Point(-2.0, -2.0)
    };
    for (const auto& point : points) {
        std::cout << "Point (" << point.getX() << ", " << point.getY()
                  << ") -> Distance: " << std::fixed << std::setprecision(3)
                  << point.distanceToOrigin() << std::endl;
    }
    std::cout << std::endl;

    auto closestPoint = std::min_element(points.begin(), points.end(),
        [](Point a,Point b) {
            return a.distanceToOrigin() < b.distanceToOrigin();
        });
    std::cout << closestPoint->getX() << '\n' << closestPoint->getY() << '\n' << closestPoint->distanceToOrigin();
    return 0;
}