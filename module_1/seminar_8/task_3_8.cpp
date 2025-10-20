#include<iostream>
#include<deque>

template<typename T>
void Addelement(std::deque<T>& buffer,const T t,const int size) {
    if (buffer.size() == size)
        buffer.pop_front();
    buffer.push_back(t);
}
template<typename T>
void PrintElements(std::deque<T>& buffer) {
    for (const auto& i : buffer) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n = 5;
    std::deque<int> buffer;
    for (int i = 0; i < 7; i++) {
        Addelement(buffer,i + 1,n);
    }
    PrintElements(buffer);
}