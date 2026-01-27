#include <concepts>
#include <iostream>
#include <vector>

// Define a simple concept
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

// Use the concept
template<Addable T>
T add(T a, T b) {
    return a + b;
}

// Constrained auto
void print_add(Addable auto a, Addable auto b) {
    std::cout << add(a, b) << '\n';
}

int main() {
    // Test with int
    std::cout << "Int test: " << add(10, 20) << '\n';
    print_add(5, 15);

    // Test with double
    std::cout << "Double test: " << add(3.14, 2.71) << '\n';

    // This would fail to compile if uncommented:
    // struct NotAddable {};
    // NotAddable na;
    // add(na, na);  // Error: constraints not satisfied

    return 0;
}