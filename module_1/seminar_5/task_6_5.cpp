#include<iostream>

int Sum(int* arr) {
    int sm = 0;
    for (int i = 0; arr[i] != 0; i++) {
        sm += arr[i];
    }
    return sm;
}


int main() {
    int n;
    std::cin >> n;
    int m = abs(n);
    int* arr = new int[m];
    int c = 0;
    while (m) {
        arr[c] = abs(m % 10);
        m = m / 10;
        c++;
    }
    int sm = Sum(arr);
    std::cout << "Sum of digits in " << n << ": ";
    for (int i = 0; i < c; i++) {
        if (i != c - 1)
        std::cout << arr[c - i - 1] << '+';
        else  std::cout << arr[c - i - 1] << ' ';
    }
    std::cout << "= " << sm << '\n';

}