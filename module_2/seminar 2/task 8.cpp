#include <iostream>
#include <cmath>
#include<numbers>

enum class ShapeType {
    Circle,
    Rectangle,
    Triangle
};

union ShapeData {
    struct { float radius; } circle;
    struct { float width, height; } rectangle;
    struct { float a, b, c; } triangle;
};

struct Shape {
    ShapeType type;
    ShapeData data;
};

float area(const Shape& shape) {
    switch (shape.type) {
        case ShapeType::Circle:
            return (M_PI * (shape.data.circle.radius * shape.data.circle.radius));

        case ShapeType::Rectangle:
            return shape.data.rectangle.height * shape.data.rectangle.width;
        case ShapeType::Triangle: {
            float a = shape.data.triangle.a;
            float b = shape.data.triangle.b;
            float c = shape.data.triangle.c;
            float p = (a + b + c) / 2.0;
            return std::sqrt(p * (p - a) * (p - b) * (p - c));
        }
            default: return 0.0;
    }
}

void printShape(const Shape& shape) {
    switch (shape.type) {
        case ShapeType::Circle:
            std::cout << "Circle radius: " << shape.data.circle.radius << '\n';
            break;
        case ShapeType::Rectangle:
            std::cout << "Rectangle width: " << shape.data.rectangle.width << '\n'
            << "Rectangle height: " << shape.data.rectangle.height << '\n';
            break;
        case ShapeType::Triangle:
            std::cout << "Triangular's: " << shape.data.triangle.a << ", " << shape.data.triangle.b << ", " << shape.data.triangle.c << '\n';
            break;
        default: std::cout << "Unknown\n";
    }
    std::cout << "Area: " << area(shape) << '\n';
}

int main() {
    Shape s1{};
    s1.type = ShapeType::Circle;
    s1.data.circle.radius = 10.0;

    Shape s2{};
    s2.type = ShapeType::Rectangle;
    s2.data.rectangle.width = 4.0;
    s2.data.rectangle.height = 6.0;

    Shape s3{};
    s3.type = ShapeType::Triangle;
    s3.data.triangle.a = 3.0;
    s3.data.triangle.b = 4.0;
    s3.data.triangle.c = 5.0;

    std::vector<Shape> shapes = {s1, s2, s3};
    for (const auto& s : shapes) {
        printShape(s);
        std::cout << "area = " << area(s) << "\n";
    }

    float total = 0.0f;
    for (const auto& s : shapes) {
        total += area(s);
    }
    std::cout << "Total area = " << total << "\n";
}