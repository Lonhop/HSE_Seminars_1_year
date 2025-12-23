#include <iostream>
#include <string>
#include <utility>
#include <vector>


class BaseMessage {
public:
    virtual ~BaseMessage() = default;
    virtual void print() const = 0;
    virtual int length() const = 0;
};

class String : public BaseMessage{
private:
    std::string str;
public:
    String(std::string str) : str(std::move(str)) {}
    int length() const override {
        if (str.empty()) {
            return 3;
        }
        return str.length();
    }
    void print() const override {
        if (str.empty()) {
            std::cout << "xyz\n";
        }
        else {
            std::cout << str << '\n';
        }
    }
};

class Multiplier : public BaseMessage {
private:
    std::string str;
    int value;
public:
    Multiplier(std::string str,int value) : str(std::move(str)), value(value) {}
    void print() const override {
        if (str.empty()) {
            std::cout << "xyz\n";
        }
        else {
            for (int i = 0; i < value; i++) {
                std::cout << str;
            }
            std::cout << '\n';
        }
    }
    int length() const override {
        return value * value;
    }
};

std::string string(std::string b,int value) {
    std::string a;
    for (int i = 0; i < value - 1;i++) {
        a += b[i];
    }
    return a;
}

int main() {
    std::vector<BaseMessage*> messages;
    std::string a,b;
    std::cin >> a >> b;
    std::cout << std::endl;
    String a1(b);
    Multiplier a2(string(a,a.length()),a.length());
    a2.print();
    a1.print();
    std::cout << a1.length() + a2.length();

    return 0;
}