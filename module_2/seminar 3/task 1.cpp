#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;
// 1) Create a triangle structure (a, b, c) with a constructor, output method, and area method.
// 2) Create a vector of 20 objects (any values).
// For each, output the area and find the triangle with the largest area.
// 3) Create a vector (push_back) of 1000 triangle values ​​by pointers and references.
//
struct Triangle {
    int a;
    int b;
    int c;
    vector<int> dummy;
public:
    Triangle(int a = 0, int b = 0, int c = 0) {
        this->a = a;
        this->b = b;
        this->c = c;
        dummy = vector<int>(100000);
    }
    void print() {
        std::cout << a << ' ' << b << ' ' << c << '\n';
    }
    double square() {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};
// Compare passing to methods.
// 1) passing by value
// 2) by reference
// 3) by pointer
// Do this 10,000 times and print the time

void pass_by_value(Triangle t) {
}
void pass_by_ref(Triangle& t) {
}
void pass_by_p(Triangle* t) {
}

int main() {
    Triangle t;
    t.a = 3;
    t.b = 4;
    t.c = 5;
    int repeats = 10000;
    t.square();
    Triangle* z = &t;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < repeats; ++i) {
        pass_by_value(t);
    };
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double,std::milli>(end - start).count() << '\n';
    auto start_1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < repeats; ++i) {
        pass_by_ref(t);
    };
    auto end_1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double,std::milli>(end_1 - start_1).count() << '\n';
    auto start_2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < repeats; ++i) {
        pass_by_p(z);
    };
    auto end_2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double,std::milli>(end_2 - start_2).count() << '\n';

}