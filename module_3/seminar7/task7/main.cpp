#include <iostream>
#include <expected>
#include <string>
#include <charconv>

std::expected<int, std::string> parse_int(const std::string& s) {
    try {
        size_t pos;
        int value = std::stoi(s, &pos);
        if (pos != s.length()) {
            return std::unexpected("Invalid characters in string");
        }
        return value;
    } catch (const std::exception&) {
        return std::unexpected("Failed to parse integer");
    }
}

std::expected<int, std::string> validate_positive(int val) {
    if (val > 0) {
        return val;
    }
    return std::unexpected("Value must be positive");
}

std::expected<int, std::string> process(const std::string& input) {
    return parse_int(input)
        .and_then(validate_positive);
}

int main() {
    std::string inputs[] = {"42", "-5", "abc", "123abc"};
    
    for (const auto& input : inputs) {
        auto result = process(input);
        if (result) {
            std::cout << "'" << input << "' -> " << *result << std::endl;
        } else {
            std::cout << "'" << input << "' -> Error: " << result.error() << std::endl;
        }
    }
    
    return 0;
}