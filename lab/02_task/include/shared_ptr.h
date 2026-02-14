#ifndef SHARED_PTR_H
#define SHARED_PTR_H


template <typename T>
class SharedPtr {
private:
    T* ptr_;
    std::size_t* count_;
public:
    SharedPtr() noexcept;
    explicit SharedPtr(T* ptr);

    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr(SharedPtr&& other) noexcept;

    SharedPtr& operator=(T* ptr);
    SharedPtr& operator=(const SharedPtr& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    ~SharedPtr();

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    void reset(T* ptr = nullptr);
    void swap(SharedPtr& other) noexcept;

    T* get() const noexcept;
    explicit operator bool() const noexcept;
};

#endif
