#include<iostream>
#include <cstddef>
#include<concepts>
#include <type_traits>


template<class T>

void swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

int main() {
    int a,b;
    std::cin >> a >> b;
    swap<int>(a,b);
    std::cout << a << ' ' << b;
}