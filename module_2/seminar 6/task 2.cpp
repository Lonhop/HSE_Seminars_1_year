#include<vector>
#include <iostream>

class ArithmeticProgression {
    int start;
    int size;
    int step;
    std::vector<int> sequence;
    void generateSequence() {
        sequence.clear();
        for (int i = 0; i < size; ++i) {
            sequence.push_back(start + i * step);
        }
    }
public:
    ArithmeticProgression(): start(0),size(0),step(0) {}
    ArithmeticProgression(const int start_1,const int size_1,const int step_1) : size(size_1), start(start_1), step(step_1) {
        if (size <= 0) {
            throw std::invalid_argument("Nothing");
        }
        generateSequence();
    }
    int getsize() { return this->size;}
    int operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("No such index");
        }
        return start + index * step;
    }
    void demonstrate() {
        for (int i = 0; i < size; ++i) {
            std::cout << (*this)[i] << '\t';
        }
        std::cout << '\n';
    }
    void getInfo() const {
        std::cout << "Start: " << start << ", Step: " << step
                  << ", Size: " << size << std::endl;
    }
};

int main() {
    ArithmeticProgression ap1(2, 3, 5);
    ap1.getInfo();
    ap1.demonstrate();

    for (int i = 0; i < ap1.getsize(); ++i) {
        std::cout << "ap1[" << i << "] = " << ap1[i] << std::endl;
    }

    return  0;
}