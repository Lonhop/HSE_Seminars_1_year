#include <iostream>

int main() {
    for (int i = 0; i < 100; i++) {
        if ((3 * i) % 17 == 8) {
            std::cout << i;
            break;
        }
    }
}