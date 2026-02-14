#include <iostream>
#include"calculator.h"

int main() {
    int sum = add(5, 3);
    std::cout << "5 + 3 = " << sum << std::endl;

    // Test subtract function
    int difference = subtract(10, 4);
    std::cout << "10 - 4 = " << difference << std::endl;

    // Test multiply function
    int product = multiply(6, 7);
    std::cout << "6 * 7 = " << product << std::endl;
}