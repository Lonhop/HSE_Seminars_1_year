#include<iostream>

int main() {
    int n;
    std::cin >> n;
    if (n >= 70) {
        if (n < 80) {
            std::cout << 'C';
        }
        if (n >= 90) {
            std::cout << 'A';
        }
        else {
            std::cout << 'B';
        }
    }
    else {
        if (n >= 60) {
            std::cout << 'D';
        }
        else {
            std::cout << 'F';
        }
    }
}