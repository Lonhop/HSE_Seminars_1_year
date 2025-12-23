#include <iostream>


class Temperature {
private:
    int celsius;
public:
    Temperature(int cels) : celsius(cels) {}
    int getCelsius() const{
        return celsius;
    }
    void setCelsius(int c) {
        celsius = c;
    }
    void print() {
        std::cout << "Temperature: " << celsius << " C\n";
    }
};

int main() {
    Temperature cl(0);
    int n;
    std::cin >> n;
    cl.setCelsius(n);
    cl.print();
    return 0;
}