#include <iostream>
#include <map>
#include <optional>
#include <string>

class Config {
private:
    std::map<std::string, int> settings;

public:
    void set(const std::string& key, int value) {
        settings[key] = value;
    }
    
    std::optional<int> get(const std::string& key) {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    int get_or_default(const std::string& key, int default_val) {
        return get(key).value_or(default_val);
    }
    
    std::optional<int> get_validated(const std::string& key, int min, int max) {
        auto value = get(key);
        if (value.has_value() && *value >= min && *value <= max) {
            return value;
        }
        return std::nullopt;
    }
};

int main() {
    Config config;
    
    // Set some values
    config.set("port", 8080);
    config.set("timeout", 30);
    
    // Test get
    auto port = config.get("port");
    std::cout << "Port: " << port.value_or(-1) << std::endl;
    
    // Test get_or_default
    std::cout << "Max connections: " 
              << config.get_or_default("max_connections", 100) << std::endl;
    
    // Test get_validated
    auto validated = config.get_validated("port", 1000, 9000);
    if (validated) {
        std::cout << "Validated port: " << *validated << std::endl;
    } else {
        std::cout << "Port is out of range" << std::endl;
    }
    
    return 0;
}