#ifndef MEPHI_LAB_SHRDPTR_H
#define MEPHI_LAB_SHRDPTR_H

#include <cstdint>

template<typename T>
class ShrdPtr {
private:
    T* ptr;
    uint64_t* m_count{};

public:
    explicit ShrdPtr(T* ptr)
        : ptr(ptr),
          m_count(new uint64_t(1)) {
    }

    ShrdPtr(const ShrdPtr &other) {
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
};

#endif //MEPHI_LAB_SHRDPTR_H
