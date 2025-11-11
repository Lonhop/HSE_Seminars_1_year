#include <iostream>

enum Colour {
    Dark,
    Green,
    White,
    Red
};

enum Cars {
    BMW,
    Mercedes,
    Ford,
    BYD
};

// enum class Colour {
//     Dark,
//     Green,
//     White,
//     Red
// };
//
// enum class Cars {
//     BMW,
//     Mercedes,
//     Ford,
//     BYD
// };

int main() {
    Colour a = Colour::Dark;
    Cars b = Cars::BMW;
    std::cout << (a == b); // 1 if enum UB if enum class
    return 0;
}