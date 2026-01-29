#include <iostream>
#include <memory>
#include<stdexcept>
#include <vector>

class ResourceManager {
private:
    std::vector<std::unique_ptr<int>> resource_;
public:
    void acquire(int value) {
        resource_.push_back(std::make_unique<int>(value));
    }
    std::unique_ptr<int> release(size_t index) {
        if (resource_.empty()) {
            throw std::runtime_error("No data(\n");
        }
        if (index >= resource_.size()) {
            throw std::runtime_error("Much more data than expected\n");
        }
        if (!resource_[index]) {
            throw std::runtime_error("Empty slot\n");
        }
        auto n = std::move(resource_[index]);
        return n;
    }
    size_t size() const {
        return resource_.size();
    }
};

int main() {
    ResourceManager mgr;
    mgr.acquire(10);
    mgr.acquire(20);
    mgr.acquire(30);
    auto res = mgr.release(1);
    std::cout << *res << "\n";
    std::cout << mgr.size() << "\n";
    return 0;
}