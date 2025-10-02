#include<iostream>

int main() {
    int a,b,c;
    std::cin >> a >> b >> c;
    if (a > b) {
        if (a > c) {
            std::cout << a << '\n';
        }
        else {
            std::cout << c << '\n';
        }
    }
    if (a < b) {
        if (b < c) {
            std::cout << c << '\n';
        }
        else {
            std::cout << b << '\n';
        }
    }
}