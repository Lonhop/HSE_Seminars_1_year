#include <iostream>
#include <vector>

bool IsPositive(int x) {
    return x > 0;
}
bool IsEven(int x) {
    return abs(x) % 2 == 0;
}

std::vector<int> filterArray(
    const std::vector<int>& arr,
    bool (*filter)(int),
    int& resultSize
) {
    std::vector<int> result;
    for (auto i : arr) {
        if (filter(i)) {
            result.push_back(i);
            resultSize++;
        }
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
        std::cin >> v[i];
    int size_1, size_2;
    size_1 = size_2 = 0;
    std::vector<int> positive_vec = filterArray(v, IsPositive, size_1);
    std::vector<int> even_vec = filterArray(v, IsEven, size_2);
    for (int i = 0; i < size_1; i++) {
        std::cout << positive_vec[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size_2; i++) {
        std::cout << even_vec[i] << " ";
    }

}