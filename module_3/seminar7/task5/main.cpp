#include <iostream>
#include <expected>
#include <cmath>
#include <string>

std::expected<double, std::string> safe_sqrt(double x) {
    if (x < 0) {
        return std::unexpected("Cannot calculate square root of negative number");
    }
    return std::sqrt(x);
}

int main() {
    // Test with positive number
    auto result1 = safe_sqrt(16.0);
    if (result1) {
        std::cout << "sqrt(16) = " << *result1 << std::endl;
    } else {
        std::cout << "Error: " << result1.error() << std::endl;
    }
    
    // Test with negative number
    auto result2 = safe_sqrt(-4.0);
    if (result2.has_value()) {
        std::cout << "sqrt(-4) = " << result2.value() << std::endl;
    } else {
        std::cout << "Error: " << result2.error() << std::endl;
    }
    
    return 0;
}