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

    UnqPtr &operator=(UnqPtr &&other) {
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

template<typename T, typename... Args>
UnqPtr<T> makeUnq(Args&&... args) {
    return UnqPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //MEPHI_LAB_UNQPTR_H
