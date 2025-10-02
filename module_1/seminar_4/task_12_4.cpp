#include<iostream>

int main() {
    double z,c;
    z = 0.1;
    while (z / 2 != 0) {
        c = z;
        z /= 10;
    }
    std::cout << c << std::endl;
}