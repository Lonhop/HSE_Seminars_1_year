#include <iostream>


template<typename T>
class vector_1 {
    T* data_1;
    size_t size_1;
    size_t capacity_1;
    void reallocate(size_t NewCapacity) {
        T* NewData = new T[NewCapacity];
        for (size_t i = 0; i < size_1; i++) {
            NewData[i] = data_1[i];
        }
        delete[] data_1;
        data_1 = NewData;
        capacity_1 = NewCapacity;
    }
public:
    vector_1() : data_1(nullptr), size_1(0), capacity_1(0) {}

    explicit vector_1(size_t InitialSize) : size_1(InitialSize), capacity_1(InitialSize) {
        data_1 = new T[capacity_1];
        for (size_t i = 0; i < size_1; i++) {
            data_1[i] = T();
        }
    }

    vector_1(size_t InitSize, const T& value) : size_1(InitSize), capacity_1(InitSize) {
        data_1 = new T[capacity_1];
        for (size_t i = 0; i < size_1; i++) {
            data_1[i] = value;
        }
    }

    vector_1 (const vector_1& other) : size_1(other.size_1), capacity_1(other.capacity_1) {
        data_1 = new T[capacity_1];
        for (size_t i = 0; i < size_1; i++) {
            data_1[i] = other.data_1[i];
        }
    }

    vector_1& operator=(const vector_1& other) {
        if (this != &other) {
            delete[] data_1 ;
            size_1 = other.size_1;
            capacity_1 = other.capacity_1;
            data_1 = new T[capacity_1];
            for (size_t i = 0; i < size_1; i++) {
                data_1[i] = other.data_1[i];
            }
        }
        return *this;
    }

    ~vector_1() {
        delete[] data_1;
    }

    T& operator[](size_t index) {
        return data_1[index];
    }

    T& at(size_t index) {
        if (index >= size_1) {
            throw std::out_of_range("Index out of range");
        }
        return data_1[index];
    }

    T& front() {
        return data_1[0];
    }

    T& back() {
        return data_1[size_1 - 1];
    }

    size_t size() const { return size_1;}
    size_t capacity() const { return capacity_1;}
    bool empty() const { return size_1 == 0; }
    void clear() { size_1 = 0;}

    void push_back(const T& value) {
        if (size_1 >= capacity_1) {
            reallocate(capacity_1 == 0 ? 1 : capacity_1 * 2);
        }
        data_1[size_1++] = value;
    }

    void pop_back() {
        if (size_1 == 0) {
            throw std::out_of_range("Vector is Empty");
        }
        --size_1;
    }
    void insert(size_t position, const T& value) {
        if (position > size_1) throw std::out_of_range("Insert position out of range");
        if (size_1 >= capacity_1) reallocate(capacity_1 == 0 ? 1 : capacity_1 * 2);
        for (size_t i = size_1; i > position; i--) {
            data_1[i] = data_1[i - 1];
        }
        data_1[position] = value;
        ++size_1;
    }

    void erase(size_t position) {
        if (position >= size_1) throw std::out_of_range("Erase position out of range");
        for (size_t i = position; i < size_1 -1; i++) {
            data_1[i] = data_1[i + 1];
        }
        --size_1;
    }

    void reverse() {
        for (size_t i = 0; i < size_1 / 2; i++) {
            std::swap(data_1[i], data_1[size_1 - 1 - i]);
        }
    }


};


int main() {
    vector_1<int> vec;
    for (int i = 1; i <= 10; i++) {
        vec.push_back(i);
    }
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
    vec.pop_back();
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';

    vec.insert(2, 77);
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';

    vec.erase(1);
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';

    vec.reverse();
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';

    std::cout << vec.front() << ' ' << vec.back() << ' ' << vec.at(8) << '\n';
    vec.clear();
    std::cout << vec.empty();
    return 0;
}