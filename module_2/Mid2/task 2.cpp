#include <iostream>
#include <vector>

class TemperatureSeq {
private:
    std::vector<int> values;
public:
    TemperatureSeq(std::vector<int> data) : values(data) {}
    void add(int v) {
        values.emplace_back(v);
    }
    int size() const{
        return values.size();
    }
    int at(int index) const{
        return values[index];
    }
    void print() {
        for (int c : values) {
            std::cout << c << " ";
        }
    }
};

int main() {
    TemperatureSeq p({});
    int n;
    while (std::cin >> n) {
        p.add(n);
    }
    std::cout << p.size() << '\n';
    p.print();
    std::cout << "\n" << p.at(4);;
    return 0;
}