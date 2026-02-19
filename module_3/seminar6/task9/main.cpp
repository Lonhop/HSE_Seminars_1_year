#include <iostream>
#include <compare>
#include <cstdint>

// ===== Task 04: constexpr Rational struct =====

struct Rational {
private:
    int64_t num;   // numerator
    int64_t den;   // denominator (> 0, fraction is reduced)
    
    // Helper function to compute GCD at compile time
    static constexpr int64_t gcd(int64_t a, int64_t b) {
        a = a < 0 ? -a : a;
        b = b < 0 ? -b : b;
        
        while (b != 0) {
            int64_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Helper to reduce fraction at compile time
    constexpr void reduce() {
        // Ensure denominator is positive
        if (den < 0) {
            num = -num;
            den = -den;
        }
        
        // Reduce by GCD
        int64_t g = gcd(num, den);
        if (g != 0 && g != 1) {
            num /= g;
            den /= g;
        }
    }
    
public:
    // constexpr constructor
    constexpr Rational(int64_t n = 0, int64_t d = 1) : num(n), den(d) {
        if (den == 0) {
            // Can't throw in constexpr, so we'll set to 0/1 as error value
            // In a real implementation, you might want to handle this differently
            num = 0;
            den = 1;
        } else {
            reduce();
        }
    }
    
    // constexpr three-way comparison using cross-multiplication
    constexpr auto operator<=>(const Rational& other) const {
        // Cross-multiplication: compare a.num * b.den vs b.num * a.den
        // Use 128-bit integers to avoid overflow
        __int128 lhs = static_cast<__int128>(num) * other.den;
        __int128 rhs = static_cast<__int128>(other.num) * den;
        
        if (lhs < rhs) return std::strong_ordering::less;
        if (lhs > rhs) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }
    
    // constexpr equality operator
    constexpr bool operator==(const Rational& other) const {
        return (*this <=> other) == 0;
    }
    
    // Getters for printing
    constexpr int64_t numerator() const { return num; }
    constexpr int64_t denominator() const { return den; }
    
    // Convert to double for display (optional)
    constexpr double to_double() const {
        return static_cast<double>(num) / den;
    }
};

// Overload << operator for easy printing
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator() << '/' << r.denominator();
    // Optionally show decimal value
    os << " (" << r.to_double() << ')';
    return os;
}

int main() {
    constexpr Rational a(1, 2);   // 0.5
    constexpr Rational b(2, 4);   // 0.5
    constexpr Rational c(3, 4);   // 0.75
    constexpr Rational d(1, 3);   // 0.333...

    // All tested at compile time
    static_assert(a == b);        // 1*4 == 2*2
    static_assert(a < c);         // 1*4=4 < 3*2=6
    static_assert(c > d);         // 3*3=9 > 1*4=4
    static_assert(d <= a);        // 1*2=2 <= 1*3=3
    static_assert(c >= b);        // 3*4=12 >= 2*4=8
    static_assert(a != c);

    static_assert((a <=> b) == std::strong_ordering::equal);
    static_assert((a <=> c) == std::strong_ordering::less);
    static_assert((c <=> d) == std::strong_ordering::greater);

    // Runtime output
    std::cout << std::boolalpha;
    std::cout << "a=1/2, b=2/4, c=3/4, d=1/3\n\n";
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a < c:  " << (a < c) << "\n";
    std::cout << "c > d:  " << (c > d) << "\n";

    std::cout << "\nAll static_asserts passed!\n";
}