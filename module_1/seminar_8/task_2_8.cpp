#include <iostream>
#include<chrono>
#include<vector>
#include<deque>
#include<list>

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = end - start;
    return dur.count();
}

template<typename Container>
double addToVectorB(int size) {
    return measureTime([size]() {
        Container container;
        for (int i = 0; i < size; i++) {
            container.insert(container.begin(), i);
        }
    });
}

int main() {
    std::cout<<addToVectorB<std::vector<int>>(100000) << std::endl;
    std::cout<<addToVectorB<std::deque<int>>(100000) << std::endl;
    std::cout<<addToVectorB<std::list<int>>(100000) << std::endl;
    return 0;
}