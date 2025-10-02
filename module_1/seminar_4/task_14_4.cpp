#include<iostream>

int main() {
    int a,b;
    std::cin >> a >> b;
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;
    std::cout << a << ' ' << b;
}