#include <iostream>
#include <cmath>

class Vector2D {
public:
    double x;
    double y;
    struct Polar {
        double r;
        double angle;

    };
    Vector2D(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Vector2D& add(double dx, double dy) {
        this->x += dx;
        this->y += dy;
        return *this;
    }
    Vector2D& scale(double k) {
        this->x *= k;
        this->y *= k;
        return *this;
    }
    Polar toPolar() {
        Polar p;
        p.r= std::sqrt(this->x * this->x + this->y * this->y);
        p.angle = std::atan2(y, x);
        return p;
    }
};
void printVector(const Vector2D& vec) {
    std::cout << "(" << vec.x << ',' << vec.y << ")" << '\n';
}
void printPolar(const Vector2D::Polar& polar) {
    std::cout << polar.r << ' ' << polar.angle << '\n';
}

int main () {
    Vector2D v{3.0, 4.0};
    v.add(1.0, -2.0)
     .scale(2.0)
     .add(-3.0, 1.0);

    auto p = v.toPolar();

    std::cout << "В декартовой форме: ";
    printVector(v);
    std::cout << "В полярной форме: ";
    printPolar(p);
    return 0;
}