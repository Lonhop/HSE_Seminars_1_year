#include<iostream>

int main() {
    int n;
    std::cin >> n;
    ((n & (n-1)) == 0) ? std::cout << "Yes" << '\n' : std::cout << "No";
}