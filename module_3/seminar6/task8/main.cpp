#include <iostream>
#include <algorithm>

// ===== Task 03: StaticArray<T, N> =====

template<typename T, std::size_t N>
class StaticArray {
private:
    T arr[N];  // C-style array
    
public:
    // constexpr default constructor (zero-initialize)
    constexpr StaticArray() : arr{} {}
    
    // constexpr constructor with initializer list (C++20)
    constexpr StaticArray(std::initializer_list<T> init) : arr{} {
        std::size_t i = 0;
        for (const T& val : init) {
            if (i >= N) break;  // ignore excess elements
            arr[i++] = val;
        }
    }
    
    // constexpr element access (non-const)
    constexpr T& operator[](std::size_t i) {
        return arr[i];
    }
    
    // constexpr element access (const)
    constexpr const T& operator[](std::size_t i) const {
        return arr[i];
    }
    
    // constexpr size getter
    constexpr std::size_t size() const {
        return N;
    }
    
    // constexpr begin/end for range-based for loops (optional but useful)
    constexpr T* begin() { return arr; }
    constexpr const T* begin() const { return arr; }
    constexpr T* end() { return arr + N; }
    constexpr const T* end() const { return arr + N; }
};

int main() {
    // Compile-time tests
    constexpr StaticArray<int, 4> arr{1, 2, 3, 4};
    static_assert(arr.size() == 4);
    static_assert(arr[0] == 1);
    static_assert(arr[1] == 2);
    static_assert(arr[2] == 3);
    static_assert(arr[3] == 4);

    // Default constructor zero-initializes
    constexpr StaticArray<int, 3> zeroed;
    static_assert(zeroed[0] == 0);
    static_assert(zeroed[1] == 0);
    static_assert(zeroed[2] == 0);

    // Runtime output
    std::cout << "arr: ";
    for (size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    std::cout << "zeroed: ";
    for (size_t i = 0; i < zeroed.size(); ++i)
        std::cout << zeroed[i] << " ";
    std::cout << "\n";

    // Mutable at runtime
    StaticArray<int, 3> mutable_arr{10, 20, 30};
    mutable_arr[1] = 99;
    std::cout << "mutable_arr[1] = " << mutable_arr[1] << "\n";

    std::cout << "\nAll static_asserts passed!\n";
}