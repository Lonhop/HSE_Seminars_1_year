#include <iostream>

class BaseNumber {
public:
    virtual ~BaseNumber() = default;
    virtual int getValue() const = 0;
    virtual void print() const = 0;
};

class RawNumber : public  BaseNumber {
private:
    int value;
public:
    RawNumber(int value) : value(value) {}
    int getValue() const override {
        return value;
    }
    void print() const override {
        std::cout << value << " ";
    }
};

class AddNumber : public BaseNumber {
private:
    int value;
public:
    AddNumber (int value) : value(value + 3) {}
    int getValue() const override {
        return value;
    }
    void print() const override {
        std::cout << value << " ";
    }
};

class MultNumber : public BaseNumber {
private:
    int value;
public:
    MultNumber (int value) : value(int(double(value) * 3.2)) {}
    int getValue() const override {
        return value;
    }
    void print() const override {
        std::cout << value;
    }
};

int main() {
    int n;
    std::cin >> n;
    RawNumber a1(n);
    AddNumber a2(n);
    MultNumber a3(n);
    int sum;
    sum = a1.getValue() + a2.getValue() + a3.getValue();
    a1.print();
    a2.print();
    a3.print();
    std::cout << "\n" << sum;
}