#include<iostream>

int main() {
    int a,b;
    std::cin >> a >> b;
    std::cout << (a | b) << " " << (a & b) << " " << (a ^ b) << " " <<
        (a >> 1) << " " << (a << 1) << " " << ~a << std::endl;
    return 0;
}