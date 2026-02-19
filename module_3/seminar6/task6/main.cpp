#include<iostream>
#include <cmath>

constexpr int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
constexpr bool is_prime(int n) {
    for (int i = 2; i < (sqrt(n) + 1); i++) {
        if (n % i == 0) return false;
    }
    return true;
}
constexpr int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int main() {
    static_assert(factorial(0) == 1);
    static_assert(factorial(5) == 120);
    static_assert(factorial(10) == 3628800);
    //
    // static_assert(is_prime(2) == true);
    // static_assert(is_prime(3) == true);
    // static_assert(is_prime(4) == false);
    // static_assert(is_prime(17) == true);
    // static_assert(is_prime(25) == false);

    static_assert(gcd(12, 8) == 4);
    static_assert(gcd(17, 19) == 1);
    static_assert(gcd(100, 75) == 25);
    static_assert(gcd(0, 5) == 5);
}
