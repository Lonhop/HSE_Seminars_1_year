#include <compare>
#include <cmath>
#include <iostream>

class Temperature {
private:
    double value;

public:
    explicit Temperature(double val = 0.0) : value(val) {}
    double getValue() const { return value; }
    void setValue(double val) { value = val; }
    std::partial_ordering operator<=>(const Temperature& other) const {
        if (std::isnan(value) || std::isnan(other.value)) {
            return std::partial_ordering::unordered;
        }
        if (value < other.value) return std::partial_ordering::less;
        if (value > other.value) return std::partial_ordering::greater;
        if (value == other.value) return std::partial_ordering::equivalent;
        return std::partial_ordering::unordered;
    }
    bool operator==(const Temperature& other) const {
        if (std::isnan(value) || std::isnan(other.value)) {
            return false;
        }
        return value == other.value;
    }
    bool operator!=(const Temperature& other) const {
        return !(*this == other);
    }
};

int main() {
    Temperature t1(36.6), t2(37.0), t3(36.6);
    Temperature nan_t(std::nan(""));

    std::cout << std::boolalpha;

    std::cout << "t1=36.6, t2=37.0, t3=36.6, nan_t=NaN\n\n";

    // Normal comparisons
    std::cout << "t1 == t3: " << (t1 == t3) << "\n";  // true
    std::cout << "t1 < t2:  " << (t1 < t2) << "\n";   // true
    std::cout << "t2 > t1:  " << (t2 > t1) << "\n";   // true
    std::cout << "t1 != t2: " << (t1 != t2) << "\n";   // true

    // NaN comparisons — all false (unordered)
    std::cout << "\nNaN comparisons (all false):\n";
    std::cout << "nan_t == t1:  " << (nan_t == t1) << "\n";   // false
    std::cout << "nan_t < t1:   " << (nan_t < t1) << "\n";    // false
    std::cout << "nan_t > t1:   " << (nan_t > t1) << "\n";    // false
    std::cout << "nan_t <= t1:  " << (nan_t <= t1) << "\n";   // false
    std::cout << "nan_t >= t1:  " << (nan_t >= t1) << "\n";   // false
    std::cout << "nan_t == nan_t: " << (nan_t == nan_t) << "\n"; // false

    // <=> directly
    auto cmp = t1 <=> nan_t;
    if (cmp == std::partial_ordering::unordered)
        std::cout << "\nt1 <=> nan_t: unordered\n";
}