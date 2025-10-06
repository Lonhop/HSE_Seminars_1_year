#include<iostream>

int reverse(const int &n) {
    int reversed = 0;
    int temp = n;
    while (temp) {
        reversed *= 10;
        reversed += temp % 10;
        temp /= 10;
    }
    return reversed;
}

int main() {
    int n;
    std::cin >> n;
    int *ptr = &n;
    int c = reverse(n);
    std::cout << "Original: " << *ptr << ", " << "Reversed: " << c <<
        " - " << ((c == *ptr) ? "Palindrome!" : "Not a palindrome!") << std::endl;
}