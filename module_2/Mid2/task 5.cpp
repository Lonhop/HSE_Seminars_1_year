#include <iostream>
#include <string>
#include <utility>
#include <vector>

class BaseShape {
protected:
    std::string name;
public:
    BaseShape(std::string name) : name(std::move(name)) {}

    virtual ~BaseShape() = default;
    virtual double area() const = 0;
    virtual void print() const = 0;
};

class Rectangle : public BaseShape{
private:
    double width;
    double height;
public:
    Rectangle(int width,double height) : width(width), height(height) {
    }

    double area() const override {
        return width * height;
    }
    void print() const override {
        std::cout << "Rectangle: Rectangle, area: " << area() << '\n';
    }
};

class Circle : public BaseShape {
private:
    double radius;
public:
    Circle(int radius) : BaseShape(name), radius(radius) {
    }


    double area() const override {
        return radius * radius * 3.14159;
    }
    void print() const override {
        std::cout << "Circle: Circle, area: "  << area() << '\n';
    }
};

int main() {
    std::vector<BaseShape*> b;
    Circle c1(1.0);
    Circle c2(2.0);
    Circle c3(3.0);
    Rectangle r1(2,1);
    Rectangle r2(3,3);
    c1.print();
    c2.print();
    c3.print();
    r1.print();
    r2.print();
    double sum = 0.0;
    sum = c1.area() + c2.area() + c3.area() +r1.area() + r2.area();
    std::cout << sum;
    return 0;
}