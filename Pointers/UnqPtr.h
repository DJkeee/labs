#ifndef MEPHI_LAB_UNQPTR_H
#define MEPHI_LAB_UNQPTR_H

template<typename T>
class UnqPtr {
private:
    T* ptr;

public:
    explicit UnqPtr(T* ptr) : ptr(ptr) {
    }

    ~UnqPtr() {
        delete ptr;
    }

    UnqPtr(const UnqPtr &other) = delete;

    UnqPtr& operator=(const UnqPtr &other) = delete;

    UnqPtr& operator=(UnqPtr &&other)
        : ptr(other.ptr) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }
};

#endif //MEPHI_LAB_UNQPTR_H
