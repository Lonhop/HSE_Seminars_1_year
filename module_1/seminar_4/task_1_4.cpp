#include<iostream>

int x = 0;

int main() {
    int x = 5;
    {
        int y = x;
        int x = 4;
        std::cout << x << '\n';
    }
    std::cout << ::x << '\n';
    std::cout << x << '\n';
    return 0;
}
