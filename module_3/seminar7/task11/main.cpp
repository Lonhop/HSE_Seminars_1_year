#include <iostream>
#include <variant>
#include <string>

struct Circle { double radius; };
struct Rectangle { double width, height; };
struct Triangle { double base, height; };

using Shape = std::variant<Circle, Rectangle, Triangle>;

std::string get_type_name(const Shape& s) {
    return std::visit([](const auto& shape) -> std::string {
        using T = std::decay_t<decltype(shape)>;
        if constexpr (std::is_same_v<T, Circle>) {
            return "Circle";
        }
        else if constexpr (std::is_same_v<T, Rectangle>) {
            return "Rectangle";
        }
        else if constexpr (std::is_same_v<T, Triangle>) {
            return "Triangle";
        }
        return "Unknown";
    }, s);
}

int main() {
    Shape shapes[] = {
        Circle{5.0},
        Rectangle{4.0, 6.0},
        Triangle{3.0, 4.0}
    };
    
    for (const auto& shape : shapes) {
        std::cout << "This shape is a: " << get_type_name(shape) << std::endl;
    }
    
    return 0;
}