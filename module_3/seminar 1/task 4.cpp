#include<iostream>
#include <utility>
#include<vector>
#include<string>

class Base {
private:
    std::string name;
public:
    explicit Base(std::string name) : name(std::move(name)) {}
    Base(const Base& other) : name(other.name) {}
    Base(Base&& other) noexcept : name(std::move(other.name)) {}
    Base& operator=(const Base& other) {
        if (this != &other) {
            name = other.name;
        }
        return *this;
    }
    Base& operator=(Base&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
        }
        return *this;
    }

    std::string GetValue() const {
        return name;
    }
    virtual ~Base() = default;

};

class Derived : public Base {
private:
    std::vector<int> data;
public:
    explicit Derived(const std::string &name) : Base(name), data(1000,37) {
    }
    Derived(const Derived& other) : Base(other), data(other.data) {}
    Derived(Derived&& other) noexcept : Base(std::move(other)), data(std::move(other.data)) {}


    Derived& operator=(const Derived& other) {
        if (this != &other) {
            Base::operator=(other);
            data = other.data;
        }
        return *this;
    }
    Derived& operator=(Derived&& other) noexcept {
            if (this != &other) {
                Base::operator=(std::move(other));
                data = std::move(other.data);
        }
        return *this;
    }
    ~Derived() override {};
};

void processByValue(Base b) {
    std::cout << "Name: " << b.GetValue() << '\n';
}

int main() {
    Base* ptr = new Derived("Damn");
    delete ptr;
    Derived d("Slice");
    processByValue(d);
    processByValue(std::move(d));
    return 0;
}

