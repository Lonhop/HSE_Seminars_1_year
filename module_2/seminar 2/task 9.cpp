#include<iostream>
#include<string>
#include<vector>
#include <cmath>

enum class ParamType {
    Int,
    Double,
    Bool,
    String
};

union ParamValue {
    int i;
    double d;
    bool b;
    char s[64];

    ParamValue() : i(0) {}
    ParamValue(int value) : i(value) {}
    ParamValue(double value) : d(value) {}
    ParamValue(bool value) : b(value) {}
    ParamValue(const char* value) {
        strncpy(s, value, 63);
        s[63] = '\0';
    }
};

struct ConfigEntry {
    std::string name;
    ParamType type;
    ParamValue value;
};

void printEntry(const ConfigEntry& config_entry) {
    std::cout << config_entry.name << " has ";
    switch (config_entry.type) {
        case ParamType::Int:
            std::cout << "int type and  it's value: " << config_entry.value.i;
            break;
        case ParamType::Double:
            std::cout << "double type and  it's value: " << config_entry.value.d;
            break;
        case ParamType::Bool:
            std::cout << "bool type and  it's value: " << (config_entry.value.b ? "true" : "false");
            break;
        case ParamType::String:
            std::cout << "string type and  it's value: " << config_entry.value.s;
            break;
    }
    std::cout << "\n";
}

void setInt(ConfigEntry& config_entry, int n) {
    config_entry.type = ParamType::Int;
    config_entry.value.i = n;
}

void setDouble(ConfigEntry& config_entry, double n) {
    config_entry.type = ParamType::Double;
    config_entry.value.d = n;
}

void setBool(ConfigEntry& config_entry, bool n) {
    config_entry.type = ParamType::Bool;
    config_entry.value.b = n;
}

void setString(ConfigEntry& config_entry, const char n[64]) {
    config_entry.type = ParamType::String;
    int c = 0;
    for (char i : config_entry.value.s) {
        i = n[c];
        c++;
    }
}

ConfigEntry* findByName(std::vector<ConfigEntry>& config,const std::string& name) {
    for (auto& entry : config) {
        if (entry.name == name) {
            return &entry;
        }
    }
    return nullptr;
}

int main() {
    std::vector<ConfigEntry> config_entries = {
        {"Radius", ParamType::Int, 64},
        {"Pi", ParamType::Double, M_PI},
        {"Human?",ParamType::Bool, true},
        {"Alex",ParamType::String,"Name"}
    };
    findByName(config_entries,"Pi")->type = ParamType::Int;
    findByName(config_entries,"Pi")->value = 3;

    for (const auto& entry : config_entries)
        printEntry(entry);

    return 0;
}