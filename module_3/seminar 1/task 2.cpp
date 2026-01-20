#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class ResourceHolder {
private:
    int* data;
    size_t size;
    
public:
    explicit ResourceHolder(size_t n = 0) : data(nullptr), size(0) {
        if (n > 0) {
            data = new int[n]();
            size = n;
        }
    }
    
    ~ResourceHolder() {
        delete[] data;
    }
    
    ResourceHolder(const ResourceHolder& other) : data(nullptr), size(0) {
        if (other.size > 0) {
            data = new int[other.size];
            size = other.size;
            std::copy(other.data, other.data + other.size, data);
        }
    }
    
    ResourceHolder& operator=(const ResourceHolder& other) {
        if (this != &other) {
            ResourceHolder temp(other);
            swap(*this, temp);
        }
        return *this;
    }
    
    ResourceHolder(ResourceHolder&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    ResourceHolder& operator=(ResourceHolder&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    size_t getSize() const noexcept { return size; }
    const int* getData() const noexcept { return data; }
    int* getData() noexcept { return data; }
    
    int& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("ResourceHolder: index out of range");
        }
        return data[index];
    }
    
    const int& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("ResourceHolder: index out of range");
        }
        return data[index];
    }
    
    int& operator[](size_t index) noexcept {
        return data[index];
    }
    
    const int& operator[](size_t index) const noexcept {
        return data[index];
    }
    
    friend void swap(ResourceHolder& a, ResourceHolder& b) noexcept {
        using std::swap;
        swap(a.data, b.data);
        swap(a.size, b.size);
    }
    
    bool isEmpty() const noexcept { return size == 0; }
    
    void print() const {
        std::cout << "ResourceHolder[size=" << size << ", data=" 
                  << static_cast<void*>(data) << "]: ";
        if (isEmpty()) {
            std::cout << "empty";
        } else {
            std::cout << "[";
            for (size_t i = 0; i < std::min(size, size_t(5)); ++i) {
                std::cout << data[i];
                if (i < std::min(size, size_t(5)) - 1) std::cout << ", ";
            }
            if (size > 5) std::cout << ", ...";
            std::cout << "]";
        }
        std::cout << "\n";
    }
};
int main() {
    std::vector<ResourceHolder> vec;
    vec.reserve(3); // why?
    vec.push_back(ResourceHolder(1000));
    vec.push_back(ResourceHolder(2000));
    vec.push_back(ResourceHolder(500));
    std::cout << "Vectr size: " << vec.size() << "\n";
    std::cout << "Element sizes: "
    << vec[0].getSize() << ", "
    << vec[1].getSize() << ", "
    << vec[2].getSize() << "\n";
    return 0;
}