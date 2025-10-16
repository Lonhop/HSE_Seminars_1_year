#include<iostream>
#include <cstddef>
#include<concepts>
#include <type_traits>


template<class T>
// requires(std::integral<T> || std::floating_point<T>)

T findMax(const T* arr, int n) {
    int mx = arr[0];
    for (int i = 0; i < n; ++i) {
        if (arr[i] > mx) mx = arr[i];
    }
    return mx;
}

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int ans = findMax<int>(arr,n);
    std::cout << ans;
    return 0;
}