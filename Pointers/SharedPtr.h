//
// Created by Dell on 12.10.2024.
//

#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <cstdint>
#include "../Pointers/UnqPtr.h"

template<typename T>
class SharedPtr {
private:
    UnqPtr<T>* ptr;
    uint64_t* m_count;

public:
    explicit SharedPtr(UnqPtr<T>& p)
        : ptr(&p), m_count(new uint64_t(1)) {
    }

    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), m_count(other.m_count) {
        ++(*m_count);
    }

    ~SharedPtr() {
        if (m_count) {
            --(*m_count);
            if (*m_count == 0) {
                delete m_count;
                delete ptr;
            }
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
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

    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr),
          m_count(other.m_count) {
        other.ptr = nullptr;
        other.m_count = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            if (m_count) {
                --(*m_count);
                if (*m_count == 0) {
                    delete m_count;
                    delete ptr;
                }
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
SharedPtr<T> makeShrd(Args&&... args) {
    auto* p = new UnqPtr<T>(new T(std::forward<Args>(args)...));
    return SharedPtr<T>(*p);
}

#endif //SHAREDPTR_H
