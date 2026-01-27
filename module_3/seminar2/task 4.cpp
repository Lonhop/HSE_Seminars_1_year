#include <iostream>
#include <array>
#include <vector>
#include <concepts>
#include <deque>
#include <list>


template <class T>
concept ResizableContainer =
    (!std::is_array_v<T>) &&                                     // Not C-array
    (!requires { typename std::tuple_size<T>::type; }) &&        // Not std::array
    requires(T c, const typename T::value_type& item) {
    typename T::value_type;                                  // has value_type
    { c.push_back(item) } -> std::same_as<void>;             // has push_back
    { c.size() } -> std::convertible_to<std::size_t>;        // has size()
    { c.clear() } -> std::same_as<void>;                     // has clear()
    };

template<ResizableContainer T>
class SafePusher {
    T container;
public:
    void add(const typename T::value_type& item) {
        container.push_back(item);
    }
    size_t count() const {
        return container.size();
    }
    void reset() {
        container.clear();
    }
};

int main() {
    SafePusher<std::vector<int>> a;
    SafePusher<std::deque<std::string>> b;
}