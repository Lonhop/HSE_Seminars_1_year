#include <iostream>
#include <string>

class Drink {
protected:
    std::string name;
    double basePrice;
public:
    Drink(std::string name, double price) : name(name), basePrice(price) {}
    virtual double price() const = 0;

};