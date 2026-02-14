#include <memory>
#include <iostream>
#include <stdexcept>

class Resource {
    int id_;
public:
    explicit Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " acquired\n";
        if (id_ == 3) {
            throw std::runtime_error("Resource 3 acquisition failed!");
        }
    }
    ~Resource() {
        std::cout << "Resource " << id_ << " released\n";
    }
};

class Transaction {
    std::unique_ptr<Resource> resource1_;
    std::unique_ptr<Resource> resource2_;
    std::unique_ptr<Resource> resource3_;
public:
    Transaction() {
        std::cout << "Attempting to acquire Resource 1...\n";
        resource1_ = std::make_unique<Resource>(1);
        std::cout << "Attempting to acquire Resource 2...\n";
        resource2_ = std::make_unique<Resource>(2);
        std::cout << "Attempting to acquire Resource 3...\n";
        resource3_ = std::make_unique<Resource>(3);
        std::cout << "Transaction completed successfully!\n";
    }
};

int main() {
    std::cout << "Starting transaction...\n";
    try {
        Transaction tx;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    std::cout << "Cleanup handled correctly via RAII\n";
}