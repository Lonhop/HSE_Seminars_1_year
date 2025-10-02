#include<iostream>


double sm(int n) {
    float b;
    b = n;
    if (b == 1) {
        return 1;
    }
    else {
        return (1.0 / n) + sm(n -1);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::cout << sm(n);
    return 0;
}