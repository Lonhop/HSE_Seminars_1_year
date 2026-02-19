#include <iostream>
#include <expected>
#include <string>

enum class ConfigError {
    NotFound,
    InvalidFormat
};

std::expected<int, ConfigError> read_port(const std::string& filename) {
    if (filename == "missing.txt") {
        return std::unexpected(ConfigError::NotFound);
    }
    if (filename == "config.err") {
        return std::unexpected(ConfigError::InvalidFormat);
    }
    return 8080;
}

int main() {
    std::string filenames[] = {"config.txt", "missing.txt", "config.err"};
    
    for (const auto& filename : filenames) {
        auto result = read_port(filename);
        
        if (result) {
            std::cout << "Port from " << filename << ": " << *result << std::endl;
        } else {
            std::cout << "Error reading " << filename << ": ";
            switch (result.error()) {
                case ConfigError::NotFound:
                    std::cout << "File not found";
                    break;
                case ConfigError::InvalidFormat:
                    std::cout << "Invalid format";
                    break;
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}