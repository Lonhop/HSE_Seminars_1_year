#include<iostream>
#include<cmath>

class Complex {
public:
    double real;
    double imaginary;
    Complex(): real(0),imaginary(0) {}
    Complex(const double& real, const double& imagine): real(real), imaginary(imagine) {}
    Complex(const Complex& other) : real(other.real), imaginary(other.imaginary) {}
    double getReal() const {
        return real;
    }
    double getImaginary() const {
        return imaginary;
    }
    void setReal(const double& rl) {
        real = rl;
    }
    void setImaginary(const double& imagine) {
        imaginary = imagine;
    }
    Complex operator+(const Complex& other) const {
        Complex ans(this->real + other.getReal(), this->imaginary + other.getImaginary());
        return ans;
    }
    Complex operator-(const Complex& other) const {
        Complex ans(this->real - other.getReal(), this->imaginary - other.getImaginary());
        return ans;
    }
    Complex operator*(const Complex& other) const {
        Complex ans(this->real * other.real - this->imaginary * other.imaginary,
                      this->real * other.imaginary + this->imaginary * other.real);
        return ans;
    }
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        if (denominator == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Complex((this->real * other.real + this->imaginary * other.imaginary) / denominator,
                      (this->imaginary * other.real - real * other.imaginary) / denominator);
    }
    bool operator==(const Complex& other) const{
        return this->real == other.real && this->imaginary == other.imaginary;
    }
    bool operator!=(const Complex& other) const{
        return !(*this == other);
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imaginary >= 0) {
        os << " + " << c.imaginary << "i";
    } else {
        os << " - " << -c.imaginary << "i";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imaginary;
    return is;
}

int main() {
    Complex z1;
    Complex z2(3.0,4.0);
    Complex z3(z2);

    z1.setReal(1.0);
    z1.setImaginary(2.0);

    std::cout << "z1: real = " << z1.getReal() << ", imaginary = " << z1.getImaginary() << '\n';
    std::cout << "z2: real = " << z2.getReal() << ", imaginary = " << z2.getImaginary() << '\n';
    std::cout << "z3: real = " << z3.getReal() << ", imaginary = " << z3.getImaginary() << '\n';

    Complex z4;
    std::cin >> z4;
    std::cout << z4 << '\n';

    return 0;
}