#include <iostream>
#include <optional>

std::optional<double> safe_divide(double a, double b) {
    if (b == 0) {
        return std::nullopt;
    }
    return a / b;
}

int main() {
    double x = 10.0, y = 2.0, z = 0.0;
    auto result1 = safe_divide(x, y);
    if (result1.has_value()) {
        std::cout << x << " / " << y << " = " << *result1 << std::endl;
    } else {
        std::cout << "Error: Division by zero!" << std::endl;
    }

    auto result2 = safe_divide(x, z);
    std::cout << x << " / " << z << " = " 
              << result2.value_or(0.0) << " (using default)" << std::endl;
    
    return 0;
}