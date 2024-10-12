#ifndef MEPHI_LAB_SHRDPTR_H
#define MEPHI_LAB_SHRDPTR_H

#include <cstdint>
#include <iostream>

template<typename T>
class ShrdPtr {
private:
    T* ptr;
    uint64_t* m_count;

    ShrdPtr(T* ptr, uint64_t* m_count) : ptr(ptr), m_count(m_count) {
    }

public:
    explicit ShrdPtr(T* ptr)
        : ptr(ptr),
          m_count(new uint64_t(1)) {
    }

    ShrdPtr(const ShrdPtr& other) {
        ptr = other.ptr;
        m_count = other.m_count;
        ++(*m_count);
    }

    ~ShrdPtr() {
        if (!m_count) {
            return;
        }
        --(*m_count);
        if (!*m_count) {
            delete m_count;
            delete ptr;
        }
    }

    ShrdPtr& operator=(const ShrdPtr& other) {
        if (this != &other) {
            if (--(*m_count) == 0) {
                delete m_count;
                delete ptr;
            }
            ptr = other.ptr;
            m_count = other.m_count;
            ++(*m_count);
        }
        return *this;
    }


    ShrdPtr(ShrdPtr&& other) noexcept {
        ptr = other.ptr;
        m_count = other.m_count;
        other.ptr = nullptr;
        other.m_count = nullptr;
    }

    ShrdPtr& operator=(ShrdPtr&& other) noexcept {
        if (this != &other) {
            if (--(*m_count) == 0) {
                delete m_count;
                delete ptr;
            }
            ptr = other.ptr;
            m_count = other.m_count;
            other.ptr = nullptr;
            other.m_count = nullptr;
        }
        return *this;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    uint64_t getCount() const {
        return *m_count;
    }
};

template<typename T, typename... Args>
ShrdPtr<T> makeShrd(Args&&... args) {
    auto* p = new T(std::forward<Args>(args)...);
    return ShrdPtr<T>(p);
}


#endif //MEPHI_LAB_SHRDPTR_H
