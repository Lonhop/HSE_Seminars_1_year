#include<iostream>
#include<string>
#include<vector>

class Counter {
public:
    int value;
    struct LogEntry {
        std::string action;
        int oldValue;
        int newValue;
    };
    std::vector<LogEntry> log;
    Counter(int initial = 0) {
        this->value = initial;
    }
    Counter& inc(int delta = 1) {
        int old = this->value;
        this->value += delta;

        this->log.push_back({"inc", old, this->value});
        return *this;
    }
    Counter& dec(int delta = 1) {
        int old = this->value;
        this->value -= delta;
        this->log.push_back({"dec", old, this->value});
        return *this;
    }
    Counter& set(int newValue) {
        int old = this->value;
        this->value = newValue;
        this->log.push_back({"set", old, this->value});
        return *this;
    }
    int getValue() const {
        return this->value;
    }
    void printLog() const {
        for (const auto& entry : this->log) {
            std::cout << entry.action << ' ' << entry.oldValue << ' ' << entry.newValue << '\n';
        }
    };
};


int main() {
    Counter c(0);
    c.inc(5).dec(2).set(10).inc();

    std::cout << "Итоговое значение: " << c.getValue() << "\n";
    std::cout << "=== Лог операций ===\n";
    c.printLog();
    return 0;
}