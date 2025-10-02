#include<iostream>

int main() {
    int a,b;
    std::cin >> a >> b;
    std::cout << (b - a ? a + (b - a): a) << std::endl;
}