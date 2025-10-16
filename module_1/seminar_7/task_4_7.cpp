#include<iostream>
#include<concepts>
#include<type_traits>

template<class T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T calculateAverage(T* arr, int n) {
    if (n == 0) {
        return T{0}; // Return zero of type T, not integer 0
    }

    T sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

int main() {
    double arr[] = {1.0, 2.0, 3.0, 4.0};

    // Let the concept deduce the type automatically
    std::cout << calculateAverage(arr, 4) << '\n';

    // Test edge case
    double empty[] = {};
    std::cout << calculateAverage(empty, 0) << '\n';

    return 0;
}