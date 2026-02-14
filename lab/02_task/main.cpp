#include <iostream>
#include "shared_ptr.h"

int main() {
    SharedPtr<int> p1(new int(15));
    SharedPtr<int> p2 = p1;
    std::cout << *p1 << ' ' << *p2 << '\n';
    p1.reset();
    std::cout << *p2 << '\n';
    return 0;
}