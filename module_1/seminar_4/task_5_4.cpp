#include<iostream>

int main() {
    int n;
    // std::cin >> n;
    n = 5;
    std::cout << ((++n) == 5) << '\n';
    std::cout << ++n << '\n';
    std::cout << n++ << '\n';
    return 0;
}