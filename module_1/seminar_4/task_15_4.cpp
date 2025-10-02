#include<iostream>

int main() {
    int n;
    std::cin >> n;
    int sm = 0;
    while (n != 0) {
        sm += n;
        n--;
    }
    std::cout << sm;
}