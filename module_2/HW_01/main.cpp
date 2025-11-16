#include<vector>
#include<list>
#include<deque>
#include<fstream>
#include <chrono>
#include <random>
#include <string>
#include<iostream>


enum class ContainerType { Vector, Deque, List };

enum class Operation {
    PushBack, PushFront, RandomInsert,
    RandomErase, IterateSum, RandomAccess
};

enum class TimeUnit { Milliseconds, Seconds };

union TimeValue {
    double ms;
    double sec;
};

struct TimeResult {
    ContainerType container;
    Operation operation;
    TimeUnit unit;
    TimeValue val;
};

std::string getContainerName(ContainerType container) {
    switch (container) {
        case ContainerType::Vector: return "vector";
        case ContainerType::Deque: return "deque";
        case ContainerType::List: return "list";
        default: return "Unknown container";
    }
}

std::string getOperationName(Operation operation) {
    switch (operation) {
        case Operation::PushBack: return "PushBack";
        case Operation::PushFront: return "PushFront";
        case Operation::RandomInsert: return "RandomInsert";
        case Operation::RandomErase: return "RandomErase";
        case Operation::IterateSum: return "IterateSum";
        case Operation::RandomAccess: return "RandomAccess";
        default: return "Unknown operation";
    }
}

template<class Seq>
double measure_push_back(int N, int repeats = 10) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);
    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start =
        std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload)
            c.push_back(x);
        auto end =
        std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double,
        std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_push_front(int N, int repeats = 10) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);
    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start =
        std::chrono::high_resolution_clock::now();
        c.clear();
        for (int x : payload) c.insert(c.begin(), x);
        auto end =
        std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double,
        std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_random_insert(int N, int repeats = 10) {
    std::vector<int> payload(N);
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);
    for (int &x : payload) x = dist(gen);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int j = 0; j < N/10; ++j) c.push_back(dist(gen));
        for (int x : payload) {
            if (c.size() > 0) {
                auto it = c.begin();
                std::advance(it, dist(gen) % c.size());
                c.insert(it, x);
            }
            else c.push_back(x);
        }
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_random_erase(int N, int repeats = 10) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int j = 0; j < N; ++j) c.push_back(dist(gen));
        while (!c.empty()) {
            auto it = c.begin();
            std::advance(it, dist(gen) % c.size());
            c.erase(it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return total / repeats;
}

template<class Seq>
double measure_iterate_sum(int N, int repeats = 10) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int j = 0; j < N; ++j) c.push_back(dist(gen));

        long long sum = 0;
        for (const auto& x : c) sum += x;
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();
        volatile long long dummy = sum;
    }
    return total / repeats;
}

template<class Seq>
double measure_random_access(int N, int repeats = 10) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 10000);

    double total = 0.0;
    Seq c;

    for (int i = 0; i < repeats; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        c.clear();
        for (int j = 0; j < N; ++j) c.push_back(dist(gen));
        long long sum = 0;
        for (int j = 0; j < 1000; ++j) {
            auto it = std::next(c.begin(), dist(gen) % c.size());
            sum += *it;
        }
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<double, std::milli>(end - start).count();

        volatile long long dummy = sum;
    }
    return total / repeats;
}

double measure_operation(ContainerType container, Operation operation, int N, int repeats = 10) {
    switch (container) {
        case ContainerType::Vector:
            switch (operation) {
                case Operation::PushBack:
                    return measure_push_back<std::vector<int>>(N, repeats);
                case Operation::PushFront:
                    return measure_push_front<std::vector<int>>(N, repeats);
                case Operation::RandomInsert:
                    return measure_random_insert<std::vector<int>>(N, repeats);
                case Operation::RandomErase:
                    return measure_random_erase<std::vector<int>>(N, repeats);
                case Operation::IterateSum:
                    return measure_iterate_sum<std::vector<int>>(N, repeats);
                case Operation::RandomAccess:
                    return measure_random_access<std::vector<int>>(N, repeats);
            }
            break;
        case ContainerType::Deque:
            switch (operation) {
                case Operation::PushBack:
                    return measure_push_back<std::deque<int>>(N, repeats);
                case Operation::PushFront:
                    return measure_push_front<std::deque<int>>(N, repeats);
                case Operation::RandomInsert:
                    return measure_random_insert<std::deque<int>>(N, repeats);
                case Operation::RandomErase:
                    return measure_random_erase<std::deque<int>>(N, repeats);
                case Operation::IterateSum:
                    return measure_iterate_sum<std::deque<int>>(N, repeats);
                case Operation::RandomAccess:
                    return measure_random_access<std::deque<int>>(N, repeats);
            }
            break;
        case ContainerType::List:
            switch (operation) {
                case Operation::PushBack:
                    return measure_push_back<std::list<int>>(N, repeats);
                case Operation::PushFront:
                    return measure_push_front<std::list<int>>(N, repeats);
                case Operation::RandomInsert:
                    return measure_random_insert<std::list<int>>(N, repeats);
                case Operation::RandomErase:
                    return measure_random_erase<std::list<int>>(N, repeats);
                case Operation::IterateSum:
                    return measure_iterate_sum<std::list<int>>(N, repeats);
                case Operation::RandomAccess:
                    return measure_random_access<std::list<int>>(N, repeats);
            }
            break;
    }
    return 0.0;
}



int main() {
    std::ofstream result_file("result.txt");
    if (!result_file.is_open()) {
        std::cerr << "Error\n";
    }

    std::vector<int> test = {8192, 32768, 262144, 1048576};
    std::vector<ContainerType> containers = {ContainerType::Vector, ContainerType::Deque, ContainerType::List};
    std::vector<Operation> operations = {
        Operation::PushBack, Operation::PushFront, Operation::RandomInsert,
        Operation::RandomErase, Operation::IterateSum, Operation::RandomAccess
    };

    for (int N : test) {
        result_file << "N=" << N << " elements\n";
        for (Operation operation : operations) {
            result_file << getOperationName(operation) << ":\n";
            for (ContainerType container : containers) {
                double time = measure_operation(container, operation, N, 10);
                result_file << '\t' << getContainerName(container) << ": " << time << " ms\n";
            }
            result_file << "\n";
        }
        result_file << "\n\n";
    }
    result_file.close();
    std::cout << "Done\n";
    return 0;
}