#include <iostream>
#include <compare>
#include <cstdint>

class Fraction {
private:
    int64_t num;
    int64_t den;
    static int64_t gcd(int64_t a, int64_t b) {
        a = std::llabs(a);
        b = std::llabs(b);
        while (b != 0) {
            int64_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    void reduce() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        int64_t g = gcd(num, den);
        if (g != 0 && g != 1) {
            num /= g;
            den /= g;
        }
    }
    
public:
    Fraction(int64_t n = 0, int64_t d = 1) : num(n), den(d) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }
    std::strong_ordering operator<=>(const Fraction& other) const {
        __int128 lhs = static_cast<__int128>(num) * other.den;
        __int128 rhs = static_cast<__int128>(other.num) * den;
        if (lhs < rhs) return std::strong_ordering::less;
        if (lhs > rhs) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }
    bool operator==(const Fraction& other) const {
        return (*this <=> other) == 0;
    }
    int64_t numerator() const { return num; }
    int64_t denominator() const { return den; }
    double to_double() const {
        return static_cast<double>(num) / den;
    }
};
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.numerator() << '/' << f.denominator();
    os << " (" << f.to_double() << ')';
    return os;
}


int main() {
    Fraction a(1, 2);   // 0.5
    Fraction b(2, 4);   // 0.5 (equivalent)
    Fraction c(3, 4);   // 0.75
    Fraction d(-1, 3);  // -0.333...

    std::cout << std::boolalpha;
    std::cout << "a=1/2, b=2/4, c=3/4, d=-1/3\n\n";

    // ==
    std::cout << "a == b: " << (a == b) << "\n";  // true  (1*4 == 2*2)
    std::cout << "a == c: " << (a == c) << "\n";  // false

    // <
    std::cout << "a < c:  " << (a < c) << "\n";   // true  (1*4=4 < 3*2=6)
    std::cout << "d < a:  " << (d < a) << "\n";   // true  (-1*2=-2 < 1*3=3)

    // >
    std::cout << "c > a:  " << (c > a) << "\n";   // true
    std::cout << "a > d:  " << (a > d) << "\n";   // true

    // <=, >=
    std::cout << "a <= b: " << (a <= b) << "\n";  // true
    std::cout << "c >= a: " << (c >= a) << "\n";  // true

    // !=
    std::cout << "a != c: " << (a != c) << "\n";  // true
}
