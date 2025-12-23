#include<iostream>
#include<vector>


class BaseNumber {
public:
    virtual ~BaseNumber() = default;
    virtual void print() const = 0;
    virtual int getValue() const = 0;

};

class Number : public BaseNumber {
private:
    int value;
public:
    Number(const int vl) : value(vl) {}
    int getValue() const override {
        return value;
    }
    void setValue(const int v) {
        value = v;
    }
    void print() const override {
        std::cout << "Number: " << value << '\t';
    }
};

class SquaredNumber : public BaseNumber {
private:
    int origin;
    int squared;
public:
    SquaredNumber(int origin) : origin(origin), squared(origin * origin) {}
    int getValue() const override {
        return origin;
    }
    void print() const override {
        std::cout << "Original: " << origin << '\n' << "Squared: " << squared;
    }
};
class DoubleNumber : public BaseNumber {
private:
    int og;
    int db;
public:
    DoubleNumber(int origin) : og(origin), db(2 * origin) {}
    int getValue() const override {
        return og;
    }
    void print() const override {
        std::cout << "Original: " << og << '\n' << "Doubled: " << db;
    }
};

class NumberCollection {
private:
    std::vector<BaseNumber*> data;
public:
    ~NumberCollection() {
        for (auto ptr : data) {
            delete ptr;
        }
        data.clear();
    }
    void add(BaseNumber* v) {
        data.push_back(v);
    }
    void printall() {
        for (auto c : data) {
            c->print();
            std::cout << '\n';
        }
    }
    int sum() const{
        int s = 0;
        for (auto ptr : data) {
            s += ptr->getValue();
        }
        return s;
    }
};




int main() {
    Number nm(0);
    nm.setValue(10);
    nm.print();
    std::cout << "\n\n";

    Number nm1(100);
    BaseNumber *ptr = &nm1;
    ptr->print();
    std::cout << "\n\n";

    NumberCollection dt;
    dt.add(new Number(5));
    dt.add(new SquaredNumber(7));
    dt.add(new DoubleNumber(13));
    dt.printall();
    std::cout << "Sum: " << dt.sum();
    std::cout << "\n";
    return 0;
}