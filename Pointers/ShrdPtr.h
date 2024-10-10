#ifndef MEPHI_LAB_SHRDPTR_H
#define MEPHI_LAB_SHRDPTR_H

#include <cstdint>

#include "UnqPtr.h"

template<typename T>
class ShrdPtr {
private:
    T* ptr;
    uint64_t* m_count{};

    class ControlBlock {
    public:
        T value;
        uint64_t m_count;
    };

    template<typename U, typename... Args>
    friend ShrdPtr<U> makeShrd(Args&&...);

    ShrdPtr(ControlBlock* cb) {

    }

public:
    explicit ShrdPtr(T* ptr)
        : ptr(ptr),
          m_count(new uint64_t(1)) {
    }

    ShrdPtr(const ShrdPtr& other) {
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
    auto* p = new typename ShrdPtr<T>::ShrdPtr(new T(std::forward<Args>(args)...),1);
    return ShrdPtr<T>(p);
}


#endif //MEPHI_LAB_SHRDPTR_H
