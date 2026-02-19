#include <iostream>
#include <vector>
#include <optional>

std::optional<size_t> find_index(const std::vector<int>& vec, int value) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // Search for existing element
    auto index1 = find_index(numbers, 30);
    if (index1.has_value()) {
        std::cout << "Found 30 at index: " << *index1 << std::endl;
    } else {
        std::cout << "30 not found" << std::endl;
    }

    // Search for non-existing element
    auto index2 = find_index(numbers, 100);
    std::cout << "100 found? "
              << (index2.has_value() ? "Yes at " + std::to_string(*index2) : "No")
              << std::endl;

    return 0;
}