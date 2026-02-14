#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr();
    explicit UniquePtr(T* p);
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    ~UniquePtr();
    T* Release();
    void Reset(T* p = nullptr);
    void Swap(UniquePtr<T>& other) noexcept;
    T* Get() const;
    T& operator*() const;
    T* operator->() const;
    explicit operator bool() const;
};

#endif