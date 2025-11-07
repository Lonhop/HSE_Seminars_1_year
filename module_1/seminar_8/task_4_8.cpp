#include<iostream>
#include<vector>
#include<algorithm>

std::vector<std::vector<int>> generate_matrix(int n, int m) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            matrix[i][j] = std::rand() % 100 - 50;
        }
    }
    return matrix;
}

void ChangeNegative(std::vector<std::vector<int>> &buffer) {
    for(int i = 0; i < buffer.size(); ++i) {
        for(int j = 0; j < buffer[i].size(); ++j) {
            if (buffer[i][j] < 0)
            buffer[i][j] = buffer[i][j] * buffer[i][j];
        }
    }
}

std::pair<long long,std::vector<int>> SumOfEven(std::vector<std::vector<int>>& buffer) {
    long long sum = 0;
    std::vector<int> odds;
    for(int i = 0; i < buffer.size(); ++i) {
        for(int j = 0; j < buffer[i].size(); ++j) {
            if (abs(buffer[i][j]) % 2 == 0)
            sum += buffer[i][j];
            else
                odds.push_back(buffer[i][j]);
        }
    }
    return std::make_pair(sum,odds);
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

void print(std::vector<std::vector<int>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size();++j)
            std::cout << vec[i][j] << ' ';
        std::cout << '\n';
    }
}

int main() {
    int row, column;
    std::cin >> row >> column;
    auto vector = generate_matrix(row,column);
    std::cout << "Original matrix:" << '\n';
    print(vector);
    std::vector<std::vector<int>> v(row, std::vector<int>(column));
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            v[i][j] = vector[i][j];
        }
    }
    ChangeNegative(v);
    std::cout << "After ChangeNegative:" << '\n';
    print(v);
    std::vector<std::vector<int>> mat(row, std::vector<int>(column));
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            mat[i][j] = vector[i][j];
        }
    }
    auto [sm,odd] = SumOfEven(mat);
    std::cout << "Sum of even elements: " << sm << '\n';
    auto lambda = [](int value) { return value == 0 ? -1 : value; };
    for(int i = 0; i < row; ++i) {
        transform_range(mat[i].begin(), mat[i].end(), lambda);
    }
    std::cout << "After transform_range:" << std::endl;
    print(mat);
    std::vector<int> odds;
    auto is_odd = [](int x) { return x % 2 != 0; };
    for (size_t i = 0; i < mat.size(); ++i) {
        copy_if_range(mat[i].begin(), mat[i].end(), std::back_inserter(odds), is_odd);
    }
    for (int i : odds)
        std::cout << i << ' ';
    return 0;
}