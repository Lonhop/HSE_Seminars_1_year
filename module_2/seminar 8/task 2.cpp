#include <iostream>
#include <string>

class Shape {
protected:
    std::string name;
public:
    virtual ~Shape() = default;

    Shape(const std::string& name) : name(name) {}
    virtual double area() const{
        return 0.0;
    }

    virtual void printInfo() const {
        std::cout << this->name;
    }
};

class Rectangle : public Shape{
private:
    double width;
    double height;
public:
    Rectangle(const std::string& name,const double& width, const double& height) : Shape(name), width(width), height(height) {}
    double area() const override {
        return width * height;
    }
    void printInfo() const override {
        std::cout << "Name: " << name << '\n'
        <<"Width: " << width << '\n'
        << "Height: " << height << '\n';
    }
};

class Circle : public  Shape {
private:
    double radius;
public:
    Circle(const std::string& name, const double radius) : Shape(name),radius(radius) {}
    double area() const override{
        return radius*radius*M_PI;
    }
    void printInfo() const override{
        std::cout << "Name: " << name << '\n'
        <<"Radius: " << radius << '\n';
    }
};

void printShapeDetails(const Shape& s) {
    s.printInfo();
    std::cout << "Area: " << s.area() << "\n\n";
}

int main() {
    Rectangle rect("MyRectangle", 3.0, 4.0);
    Circle circ("MyCircle", 5.0);

    printShapeDetails(rect);
    printShapeDetails(circ);

    Shape* shapes[2];
    shapes[0] = &rect;
    shapes[1] = &circ;

    for (int i = 0; i < 2; i++) {
        shapes[i]->printInfo();
        std::cout << "Area: " << shapes[i]->area() << std::endl << std::endl;
    }

    Shape* shapePtr = new Rectangle("Dynamic Rectangle", 4.0, 6.0);
    delete shapePtr;

    return 0;
}
