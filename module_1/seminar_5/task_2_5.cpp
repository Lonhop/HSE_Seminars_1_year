#include<iostream>

bool reverse(int* arr) {
    int* temp = arr;
    for (int i = 0; i < sizeof(temp); i++) {
        if (temp[i] != *(temp - i)) {
            std::cout << temp[i] << " " << *(temp + i);
        return false;
        }
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = n % 10;
        n /= 10;
    }
    std::cout << reverse(arr);
}