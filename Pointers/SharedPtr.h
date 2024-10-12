//
// Created by Dell on 12.10.2024.
//

#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <cstdint>
#include "../Pointers/UnqPtr.h"


template<typename T>
class ShrdPtr {
private:
    UnqPtr<T>* ptr;
    uint64_t* m_count;

public:
    explicit ShrdPtr(UnqPtr<T>& p)
        : ptr(&p), m_count(new uint64_t(1)) {
    }

    ShrdPtr(const ShrdPtr& other)
        : ptr(other.ptr), m_count(other.m_count) {
        ++(*m_count);
    }

    ~ShrdPtr() {
        if (--(*m_count) == 0) {
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

    ShrdPtr(ShrdPtr&& other) noexcept
        : ptr(other.ptr),
          m_count(other.m_count) {
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
        return ptr->get();
    }

    T* get() const {
        return ptr->get();
    }

    T& operator*() const {
        return *ptr->get();
    }

    uint64_t getCount() const {
        return *m_count;
    }
};

template<typename T, typename... Args>
ShrdPtr<T> makeShrd(Args&&... args) {
    auto* p = new UnqPtr<T>(new T(std::forward<Args>(args)...));
    return ShrdPtr<T>(*p);
}

#endif //SHAREDPTR_H
