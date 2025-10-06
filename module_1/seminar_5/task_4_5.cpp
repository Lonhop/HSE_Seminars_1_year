#include<iostream>

int* table(const int &n) {
    int* temp = new int[n];
    for (int i = 1; i <= 10; i++) {
        temp[i] = n * i;
    }
    return temp;
}

int main() {
    int n;
    std::cin >> n;
    int* ptr = table(n);
    for (int i = 1; i <= 10; i++) {
        std::cout << n << " * " << i << " = " << ptr[i] << '\n';
    }
    return 0;
}