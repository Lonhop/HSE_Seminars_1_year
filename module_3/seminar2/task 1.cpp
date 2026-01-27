#include<iostream>

// Define our own concepts from scratch
template<typename T, typename U>
concept same_as = requires {
    // This is how same_as is typically implemented
    // We need to check both directions
    requires std::is_same_v<T, U>;  // But std::is_same_v needs <type_traits>
};

// Without any standard headers, we need to implement our own type traits
namespace my_traits {
    // Basic type checking using template specialization
    template<typename T, typename U>
    struct is_same {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };

    template<typename T>
    struct is_pointer {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_pointer<T*> {
        static constexpr bool value = true;
    };
}

// Now define concepts using our traits
template<typename T, typename U>
concept same_as = my_traits::is_same<T, U>::value;

template<typename T>
concept is_pointer = my_traits::is_pointer<T>::value;

// Use the concepts
template<typename T>
struct TypeInfo {
    static void print() {
        std::cout << "Type is generic" << '\n';
    }
};

template<same_as<int> T>
struct TypeInfo<T> {
    static void print() {
        std::cout << "Type is integer" << '\n';
    }
};

template<same_as<double> T>
struct TypeInfo<T> {
    static void print() {
        std::cout << "Type is double" << '\n';
    }
};

template<is_pointer T>
struct TypeInfo<T> {
    static void print() {
        std::cout << "Type is pointer" << '\n';
    }
};

int main() {
    TypeInfo<char>::print();
    TypeInfo<int>::print();
    TypeInfo<double>::print();
    TypeInfo<float*>::print();
    TypeInfo<int*>::print();
    return 0;
}