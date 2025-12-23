#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <cmath>


class BaseShape {
public:
    virtual ~BaseShape() = default;
    virtual void print() const = 0;
    virtual double getArea() const = 0;
};

class Shape :  public BaseShape{
private:
    std::string name;
    double area;
public:
    Shape(std::string name, double area) : name(std::move(name)), area(area){}
    std::string getName() const {
        return name;
    }
    double getArea() const override {
        return area;
    }
    void setName(const std::string& nm) {
        name = nm;
    }

    void print() const override{
        std::cout << "Shape: " << name << ' ' << area << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << "Shape: " << shape.name;
        return os;
    }
};

class Circle : public BaseShape {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}
    double getArea() const override {
        return (radius * radius * M_PI);
    }
    void print() const override {

        std::cout << "Circle with radius R: " << std::fixed << std::setprecision(2) <<  getArea() <<'\n';
    }
};

class Rectangle : public BaseShape {
private:
    double width;
    double height;
public:
    Rectangle (double width, double height) : width(width), height(height) {}
    double getArea() const override {
        return (height * width);
    }
    void print() const override {
        std::cout << "Rectangle W x H: " << getArea() << '\n';
    }
};




class ShapeCollection {
private:
    std::vector<BaseShape*> shapes;
public:
    ~ShapeCollection() {
        for (auto ptr : shapes) {
            delete ptr;
        }
        shapes.clear();
    }
    void add(BaseShape* name) {
        shapes.push_back(name);
    }
    double totalArea() const{
        double sum = 0;
        for (const auto& shape : shapes) {
            sum += shape->getArea();
        }
        return sum;
    }
    void PrintAll() {
        for (auto shape : shapes) {
            shape->print();
        }
    }

};


int main() {
    ShapeCollection b;
    b.add(new Shape("Triangle",12.50));
    b.add(new Circle(3.0));
    b.add(new Rectangle(4,5));
    b.PrintAll();
    std::cout << "Total Area: " << b.totalArea() << '\n';
}