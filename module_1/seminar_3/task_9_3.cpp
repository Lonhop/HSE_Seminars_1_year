#include <iomanip>
#include<iostream>

int main() {
    float n;
    std::cin >> n;
    std::cout << std::fixed << std::setprecision(2) << n << std::endl;
    int a;
    a = n;
    std::cout << std::hex << a << std::endl;
    std::cout << std::oct << a << std::endl;
    std::cout << std::dec << a << std::endl;
    return 0;
}