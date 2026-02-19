#include <iostream>
#include <compare>
#include <cmath>

// ===== Task 02: Point with constexpr members =====

struct Point {
    int x;
    int y;
    
    // constexpr constructor
    constexpr Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    
    // constexpr distance squared
    constexpr double distance_squared(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return static_cast<double>(dx * dx + dy * dy);
    }
    
    // constexpr equality operator
    constexpr bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    // defaulted spaceship operator (constexpr by default)
    constexpr auto operator<=>(const Point& other) const = default;
};

int main() {
    constexpr Point a(1, 2);
    constexpr Point b(4, 6);
    constexpr Point c(1, 2);

    // Compile-time checks
    static_assert(a == c);
    static_assert(a != b);
    static_assert(a < b);
    static_assert(b > a);
    static_assert(a.distance_squared(b) == 25.0);  // (4-1)^2 + (6-2)^2 = 9+16 = 25

    constexpr double dist = a.distance_squared(b);
    static_assert(dist == 25.0);

    // Runtime output
    std::cout << std::boolalpha;
    std::cout << "a={1,2}, b={4,6}, c={1,2}\n\n";
    std::cout << "a == c: " << (a == c) << "\n";
    std::cout << "a < b:  " << (a < b) << "\n";
    std::cout << "a.distance_squared(b) = " << a.distance_squared(b) << "\n";

    std::cout << "\nAll static_asserts passed!\n";
}



