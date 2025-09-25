#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::cout << abs(n % 10) + abs(n / 1000) + abs(n / 10 % 10) + abs(n / 100 % 10) << std::endl;
    return 0;
}