#include <iostream>
#include <string>

class User {
public:
    std::string name;
    int id;

    class Address {
    public:
        std::string city;
        std::string street;
        int house;

        std::string toString() const {
            std::string strs = this->city + "-" + this->street + "-" + std::to_string(this->house);
            return strs;
        }
    };

    Address address;

    User(std::string name, int id, const Address& addr) : name(name), id(id), address(addr) {}

    User(const User& other)
        : name(other.name), id(other.id), address(other.address) {}

    User& operator=(const User& other) {
        if (this == &other) {
            return *this;
        }
        this->name = other.name;
        this->id = other.id;
        this->address = other.address;

        return *this;
    }

    std::string toString() const {
        return "User[name=" + this->name +
               ", id=" + std::to_string(this->id) +
               ", address=" + this->address.toString() + "]";
    }
};

int main() {
    User::Address addr{"Moscow", "Tverskaya", 10};
    User u1{"Иван", 1, addr};

    User u2 = u1;
    u2 = u2;

    std::cout << u1.toString() << "\n";
    std::cout << u2.toString() << "\n";
    return 0;
}