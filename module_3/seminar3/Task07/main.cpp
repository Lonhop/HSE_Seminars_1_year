#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>

template<class T>
class VectorLike {
    std::vector<T> data;
public:
    VectorLike(std::initializer_list<T> il) : data(il) { std::cout << "ilist\n";}

    VectorLike(const VectorLike&) { std::cout << "copy\n";}

    VectorLike(VectorLike&&) noexcept {std::cout << "move\n";}

    template<class U, typename std::enable_if<
        !std::is_same<typename std::remove_cv<typename std::remove_reference<U>::type>::type, VectorLike<T>>::value &&
        !std::is_same<typename std::remove_cv<typename std::remove_reference<U>::type>::type, std::initializer_list<T>>::value &&
        std::is_constructible<std::vector<T>, U&&>::value
    , int>::type = 0>
    explicit VectorLike(U&& u) : data(std::forward<U>(u)) { std::cout << "templ\n";}
};

int main() {
    VectorLike<int> v1{1, 2, 3};
    VectorLike<int> v2(v1);
    VectorLike<int> v3(std::move(v1));
    VectorLike<int> v4(5);
    return 0;
}