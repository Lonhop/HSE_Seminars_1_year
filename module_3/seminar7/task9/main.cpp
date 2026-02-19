#include <iostream>
#include <variant>
#include <string>



void print_value(const std::variant<int, double, std::string> v) {
    if (std::holds_alternative<int>(v)) {
        std::cout << "int: " << std::get<int>(v) << std::endl;
    }
    else if (std::holds_alternative<double>(v)) {
        std::cout << "double: " << std::get<double>(v) << std::endl;
    }
    else if (std::holds_alternative<std::string>(v)) {
        std::cout << "string: " << std::get<std::string>(v) << std::endl;
    }
}

int main() {
    std::variant<int, double, std::string> v1 = 42;
    std::variant<int, double, std::string> v2 = 3.14;
    std::variant<int, double, std::string> v3 = std::string("Hello, World!");

    print_value(v1);
    print_value(v2);
    print_value(v3);

    return 0;
}