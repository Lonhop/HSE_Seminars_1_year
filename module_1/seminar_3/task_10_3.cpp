#include"math_operators.h"
#include<iostream>

int main() {
    int a,b;
    std::cin >> a >> b;
    std::cout << plus(a,b) << std::endl;
    std::cout << minus(a,b) << std::endl;
    std::cout << multiply(a,b) << std::endl;
    std::cout << divide(a,b) << std::endl;
}

