#include<iostream>
#include<vector>
#include<algorithm>

void GenerateVector(std::vector<int>& buffer,int const row, int const col) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            buffer[i * col + j] = -50 + (rand() % 100);
        }
    }
}

void ChangeNegative(std::vector<int>& buffer, int const row, int const col) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if (buffer[i * col + j] < 0)
            buffer[i * col + j] = buffer[i * col + j] * buffer[i * col + j];
        }
    }
}

int SumOfEven(std::vector<int>& buffer, int const row, int const col) {
    int sum = 0;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if (abs(buffer[i * col + j]) % 2 == 0)
            sum += buffer[i * col + j];
        }
    }
    return sum;
}

template < class ForwardIt , class UnaryOp >
void transform_range(ForwardIt first, ForwardIt last, UnaryOp op) {
    std::transform(first, last, first, op);
}

template <class InputIt, class OutputIt, class Pred>
OutputIt copy_if_range(InputIt first, InputIt last, OutputIt out, Pred p) {
    for (auto i = first; i != last; ++i) {
        if (p(*i)) {
            *out = *i;
            ++out;
        }
    }
    return out;
}

int main() {
    int row, column;
    std::cin >> row >> column;
    std::vector<int> vector(row * column);
    GenerateVector(vector,row,column);
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            std::cout << vector[i * column + j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    // ChangeNegative(vector, row, column);
    // for(int i = 0; i < row; ++i) {
    //     for(int j = 0; j < column; ++j) {
    //         std::cout << vector[i * column + j] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    std::cout << SumOfEven(vector, row, column) << '\n';
    std::cout << '\n';
    std::vector<std::vector<int>> mat(row, std::vector<int>(column));
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            mat[i][j] = vector[i * column + j];
        }
    }
    // auto lambda = [](int value) { return value == 0 ? -1 : value; };
    // for(int i = 0; i < row; ++i) {
    //     transform_range(mat[i].begin(), mat[i].end(), lambda);
    // }
    // for(int i = 0; i < row; ++i) {
    //     for(int j = 0; j < column; ++j) {
    //         std::cout << mat[i][j] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    std::vector<int> odds;
    auto isOdd = [](int value) { return value % 2 != 0; };
    for(int i = 0; i < row; ++i) {
        copy_if_range(mat[i].begin(), mat[i].end(), std::back_inserter(odds), isOdd);
    }
    for(int num : odds) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;
    return 0;
}