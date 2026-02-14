#include "unique_ptr.h"
#include <utility>

template <typename T>
UniquePtr<T>::UniquePtr() : ptr(nullptr) {}

template <typename T>
UniquePtr<T>::UniquePtr(T* p) : ptr(p) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete ptr;
}

template <typename T>
T* UniquePtr<T>::Release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

template <typename T>
void UniquePtr<T>::Reset(T* p) {
    if (ptr != p) {
        delete ptr;
        ptr = p;
    }
}

template <typename T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) noexcept {
    std::swap(ptr, other.ptr);
}

template <typename T>
T* UniquePtr<T>::Get() const {
    return ptr;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return ptr;
}

template <typename T>
UniquePtr<T>::operator bool() const {
    return ptr != nullptr;
}

template class UniquePtr<int>;