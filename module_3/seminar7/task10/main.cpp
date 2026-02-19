#include <iostream>
#include <variant>
#include <cmath>

struct Circle {
    double radius;
};

struct Rectangle {
    double width;
    double height;
};

struct Triangle {
    double base;
    double height;
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

double get_area(const Shape& s) {
    return std::visit([](const auto& shape) -> double {
        using T = std::decay_t<decltype(shape)>;
        if constexpr (std::is_same_v<T, Circle>) {
            return M_PI * shape.radius * shape.radius;
        }
        else if constexpr (std::is_same_v<T, Rectangle>) {
            return shape.width * shape.height;
        }
        else if constexpr (std::is_same_v<T, Triangle>) {
            return 0.5 * shape.base * shape.height;
        }
        return 0;
    }, s);
}

int main() {
    Shape shapes[] = {
        Circle{5.0},
        Rectangle{4.0, 6.0},
        Triangle{3.0, 4.0}
    };
    
    for (const auto& shape : shapes) {
        std::cout << "Area: " << get_area(shape) << std::endl;
    }
    
    return 0;
}