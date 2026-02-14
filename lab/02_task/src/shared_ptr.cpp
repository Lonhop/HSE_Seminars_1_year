#include <utility>
#include "shared_ptr.h"

template <typename T>
SharedPtr<T>::SharedPtr() noexcept : ptr_(nullptr), count_(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : ptr_(ptr) {
    if (ptr_) {
        count_ = new std::size_t(1);
    } else {
        count_ = nullptr;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
    if (count_) {
        ++(*count_);
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
    other.ptr_ = nullptr;
    other.count_ = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(T* ptr) {
    reset(ptr);
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) noexcept {
    if (this != &other) {
        if (count_) {
            --(*count_);
            if (*count_ == 0) {
                delete ptr_;
                delete count_;
            }
        }
        ptr_ = other.ptr_;
        count_ = other.count_;
        if (count_) {
            ++(*count_);
        }
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        if (count_) {
            --(*count_);
            if (*count_ == 0) {
                delete ptr_;
                delete count_;
            }
        }
        ptr_ = other.ptr_;
        count_ = other.count_;
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }
    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (count_) {
        --(*count_);
        if (*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }
}

template <typename T>
T& SharedPtr<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
T* SharedPtr<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) {
    if (count_) {
        --(*count_);
        if (*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }
    if (ptr) {
        ptr_ = ptr;
        count_ = new std::size_t(1);
    } else {
        ptr_ = nullptr;
        count_ = nullptr;
    }
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(count_, other.count_);
}

template <typename T>
T* SharedPtr<T>::get() const noexcept {
    return ptr_;
}

template <typename T>
SharedPtr<T>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template class SharedPtr<int>;