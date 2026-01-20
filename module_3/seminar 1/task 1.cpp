#include<iostream>
#include<vector>
#include <chrono>
#include<utility>

class NoMoveBuffer {
private:
    std::vector<char> data;
public:
    explicit NoMoveBuffer(size_t size) : data(size,'A') {}
    NoMoveBuffer(const NoMoveBuffer& other) : data(other.data) {}
    NoMoveBuffer& operator=(const NoMoveBuffer& other) {
        if (this != &other) data = other.data;
        return *this;
    }
    NoMoveBuffer(NoMoveBuffer&&) = delete;
    NoMoveBuffer& operator=(NoMoveBuffer&&) = delete;

    friend void swap(NoMoveBuffer& a, NoMoveBuffer& b) noexcept {
        NoMoveBuffer temp = a;
        a = b;
        b = temp;
    }
    size_t size() const { return data.size();}

};
class MoveBuffer {
private:
    std::vector<char> data;
public:
    explicit MoveBuffer(size_t size) : data(size,'A') {}
    MoveBuffer(const MoveBuffer& other) : data(other.data) {}
    MoveBuffer& operator=(const MoveBuffer& other) {
        if (this != &other) data = other.data;
        return *this;
    }
    MoveBuffer(MoveBuffer&& other) noexcept : data(std::move(other.data)) {}
    MoveBuffer& operator=(MoveBuffer&& other) noexcept {
        if (this != &other) data = std::move(other.data);
        return *this;
    }
    ~MoveBuffer() = default;
    size_t size() const { return data.size();}

};

template<typename T>
void benchmark_swap(const T& buffer_1,const T& buffer_2) {
    T a = buffer_1;
    T b = buffer_2;

    std::cout << "Starting\n";

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; i++) {
        using std::swap;
        swap(a,b);
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Result: " << duration.count() << '\n';
    std::cout << "Average time: " << duration.count() / 100 << "\n\n";
}


int main() {
    const size_t Buffer_size = 10000;

    NoMoveBuffer NoMove1(Buffer_size);
    NoMoveBuffer NoMove2(Buffer_size);

    MoveBuffer move1(Buffer_size);
    MoveBuffer move2(Buffer_size);
    {
        NoMoveBuffer a(Buffer_size);
        NoMoveBuffer b(Buffer_size);
        swap(a,b);
    }
    {
        MoveBuffer a(Buffer_size);
        MoveBuffer b(Buffer_size);
        std::swap(a,b);
    }

    benchmark_swap(NoMove1,NoMove2);
    benchmark_swap(move1,move2);

    const size_t BufferSize = 100000;

    NoMoveBuffer nomove1(BufferSize);
    NoMoveBuffer nomove2(BufferSize);

    MoveBuffer Move1(BufferSize);
    MoveBuffer Move2(BufferSize);
    {
        NoMoveBuffer a(BufferSize);
        NoMoveBuffer b(BufferSize);
        swap(a,b);
    }
    {
        MoveBuffer a(BufferSize);
        MoveBuffer b(BufferSize);
        std::swap(a,b);
    }

    benchmark_swap(nomove1,nomove2);
    benchmark_swap(Move1,Move2);
    return 0;
}