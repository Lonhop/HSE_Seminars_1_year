#include<iostream>
#include <cstddef>
#include<concepts>
#include <type_traits>


template<class T>

void swap(T* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) std::swap(a[j],a[j + 1]);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    swap<int>(arr,n);
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}