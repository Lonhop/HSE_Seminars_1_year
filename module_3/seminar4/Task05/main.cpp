#include <memory>
#include <iostream>
#include <stdexcept>

class Matrix {
    std::unique_ptr<double[]> data_;
    size_t rows_, cols_;

public:
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(new double[rows * cols]) {
        std::fill_n(data_.get(), rows_ * cols_, 0.0);
    }

    double& operator()(size_t row, size_t col) {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data_[row * cols_ + col];
    }

    double operator()(size_t row, size_t col) const {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data_[row * cols_ + col];
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    void print() const {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Matrix m(3, 4);
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            m(i, j) = i * 10 + j;
        }
    }
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            std::cout << m(i, j) << " ";
        }
        std::cout << "\n";
    }
}