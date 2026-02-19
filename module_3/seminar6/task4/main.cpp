#include <iostream>
#include <compare>

class LegacyInt {
private:
    int value;
public:
    explicit LegacyInt(int v) : value(v) {}
    bool operator==(const LegacyInt& other) const {
        return value == other.value;
    }
    bool operator<(const LegacyInt& other) const {
        return value < other.value;
    }
    bool operator>(const LegacyInt& other) const {
        return value > other.value;
    }
    int get_value() const { return value; }
};



class ModernInt {
private:
    int value;
public:
    explicit ModernInt(int v) : value(v) {}
    auto operator<=>(const ModernInt&) const = default;
    int get_value() const { return value; }
};



std::ostream& operator<<(std::ostream& os, const LegacyInt& li) {
    return os << li.get_value();
}

std::ostream& operator<<(std::ostream& os, const ModernInt& mi) {
    return os << mi.get_value();
}

int main() {
    std::cout << std::boolalpha;

    // LegacyInt tests
    LegacyInt la(3), lb(5), lc(3);
    std::cout << "=== LegacyInt ===\n";
    std::cout << "la=3, lb=5, lc=3\n";
    std::cout << "la == lc: " << (la == lc) << "\n";  // true
    std::cout << "la == lb: " << (la == lb) << "\n";  // false
    std::cout << "la < lb:  " << (la < lb) << "\n";   // true
    std::cout << "lb > la:  " << (lb > la) << "\n";   // true

    // ModernInt tests
    ModernInt ma(3), mb(5), mc(3);
    std::cout << "\n=== ModernInt ===\n";
    std::cout << "ma=3, mb=5, mc=3\n";
    std::cout << "ma == mc: " << (ma == mc) << "\n";  // true
    std::cout << "ma == mb: " << (ma == mb) << "\n";  // false
    std::cout << "ma < mb:  " << (ma < mb) << "\n";   // true
    std::cout << "mb > ma:  " << (mb > ma) << "\n";   // true

    // ModernInt also gets !=, <=, >= for free
    std::cout << "\nModernInt bonus operators (from <=>):\n";
    std::cout << "ma != mb: " << (ma != mb) << "\n";  // true
    std::cout << "ma <= mc: " << (ma <= mc) << "\n";  // true
    std::cout << "mb >= ma: " << (mb >= ma) << "\n";  // true
}