#include<iostream>
#include "unique_ptr.h"

int main() {
    UniquePtr<int> ptr(new int(15));
    std::cout << *ptr << '\n';
    UniquePtr<int> ptr_2 = std::move(ptr);
    std::cout << *ptr_2 << '\n';
    return 0;
}
