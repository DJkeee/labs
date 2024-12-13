#ifndef MEPHI_LAB_SHRDPTR_H
#define MEPHI_LAB_SHRDPTR_H

#include <cstdint>
#include <iostream>

template<typename T>
class SmartPtr {
private:
    T* ptr;
    uint64_t* m_count;

    SmartPtr(T* ptr, uint64_t* m_count) : ptr(ptr), m_count(m_count) {
    }

public:
    explicit SmartPtr(T* ptr)
        : ptr(ptr),
          m_count(new uint64_t(1)) {
    }

    SmartPtr(const SmartPtr& other) {
        ptr = other.ptr;
        m_count = other.m_count;
        ++(*m_count);
    }

    ~SmartPtr() {
        if (!m_count) {
            return;
        }
        --(*m_count);
        if (!*m_count) {
            delete m_count;
            delete ptr;
        }
    }

    SmartPtr& operator=(const SmartPtr& other) {
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


    SmartPtr(SmartPtr&& other) noexcept {
        ptr = other.ptr;
        m_count = other.m_count;
        other.ptr = nullptr;
        other.m_count = nullptr;
    }

    SmartPtr& operator=(SmartPtr&& other) noexcept {
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
SmartPtr<T> makeSmart(Args&&... args) {
    auto* p = new T(std::forward<Args>(args)...);
    return SmartPtr<T>(p);
}


#endif //MEPHI_LAB_SHRDPTR_H
