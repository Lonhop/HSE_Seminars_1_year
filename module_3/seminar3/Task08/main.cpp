#include <iostream>
#include <type_traits>
#include <utility>

template<class T>
class StrongNumber {
    T value;
public:
    StrongNumber(const StrongNumber&) { std::cout << "copy\n";}

    StrongNumber(StrongNumber&&) noexcept { std::cout << "move\n";}

    template<class U, typename std::enable_if<
        !std::is_same<typename std::remove_cv<typename std::remove_reference<U>::type>::type, StrongNumber<T>>::value &&
        std::is_constructible<T, U&&>::value
    , int>::type = 0>
    explicit StrongNumber(U&& u) : value(std::forward<U>(u)) { std::cout << "templ\n";}
};

int main() {
    StrongNumber<int> sn1(10);
    StrongNumber<int> sn3(sn1);
    StrongNumber<int> sn4(std::move(sn1));
    StrongNumber<double> sn5(3.14f);
    return 0;
}