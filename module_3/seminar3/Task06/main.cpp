#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

template<class T>
class Box {
    T value;
public:
    Box(const Box&) { std::cout << "copy\n";}
    Box(Box&&) noexcept {}
    template<class U, typename std::enable_if<
        !std::is_same<typename std::remove_cv<typename std::remove_reference<U>::type>::type, Box<T>>::value &&
        std::is_constructible<T, U&&>::value
    , int>::type = 0>
    explicit Box(U&& u) : value(std::forward<U>(u)) { std::cout << "templ\n";}
};

int main() {
    Box<int> a(10);
    Box<int> b(a);
    Box<int> c(std::move(a));
    Box<std::string> s("hi");

    return 0;
}