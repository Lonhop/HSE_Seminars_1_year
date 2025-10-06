#include<iostream>

int Digit(int* arr) {
    int count = 1;
    for (int i = 1; arr[i] != 0; i++) {
        count++;
    }
    return count;
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    int c = 0;
    int m = n;
    while (m) {
        arr[c] = m % 10;
        m = m / 10;
        c++;
    }
    int count = Digit(arr);
    std::cout << "Number " << n << " has " << count << " digits";

}