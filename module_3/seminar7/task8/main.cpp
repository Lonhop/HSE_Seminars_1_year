#include <iostream>
#include <expected>
#include <string>

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

int main() {
    std::string inputs[] = {"5", "10", "abc"};
    
    for (const auto& input : inputs) {
        auto result = parse_int(input)
            .transform([](int x) { return x * x; });
        
        if (result) {
            std::cout << "'" << input << "' squared = " << *result << std::endl;
        } else {
            std::cout << "'" << input << "' -> Error: " << result.error() << std::endl;
        }
    }
    
    return 0;
}