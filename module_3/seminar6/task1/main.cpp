#include<compare>
#include<iostream>


std::strong_ordering;

struct Point {
    int x;
    int y;
    auto operator<=>(const Point&) const = default;
};

int main() {
    Point a{1, 2}, b{1, 3}, c{1, 2}, d{2, 0};

    std::cout << std::boolalpha;

    std::cout << "a={1,2}, b={1,3}, c={1,2}, d={2,0}\n\n";

    // operator==
    std::cout << "a == c: " << (a == c) << "\n";  // true
    std::cout << "a == b: " << (a == b) << "\n";  // false

    // operator!=
    std::cout << "a != b: " << (a != b) << "\n";  // true
    std::cout << "a != c: " << (a != c) << "\n";  // false

    // operator<
    std::cout << "a < b:  " << (a < b) << "\n";   // true (same x, 2 < 3)
    std::cout << "b < a:  " << (b < a) << "\n";   // false

    // operator>
    std::cout << "d > a:  " << (d > a) << "\n";   // true (2 > 1)
    std::cout << "a > d:  " << (a > d) << "\n";   // false

    // operator<=
    std::cout << "a <= c: " << (a <= c) << "\n";  // true
    std::cout << "a <= b: " << (a <= b) << "\n";  // true

    // operator>=
    std::cout << "b >= a: " << (b >= a) << "\n";  // true
    std::cout << "a >= d: " << (a >= d) << "\n";  // false

    // <=> directly
    auto cmp = a <=> b;
    if (cmp < 0)      std::cout << "\na <=> b: less\n";
    else if (cmp == 0) std::cout << "\na <=> b: equal\n";
    else               std::cout << "\na <=> b: greater\n";
}