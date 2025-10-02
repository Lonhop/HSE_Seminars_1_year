#include<iostream>

int main() {
    int n;
    std::cin >> n;
    int c = 0;
    while (n != 0) {
        n &= n - 1;
        c += 1;
    }
    std::cout << c;
}