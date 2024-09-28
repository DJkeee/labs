#ifndef MEPHI_LAB_SHRDPTR_H
#define MEPHI_LAB_SHRDPTR_H
#include "UnqPtr.h"

template <typename T>
class SharedPtr {
private:
UnqPtr<T> ptr;
int* counter;

public:
SharedPtr();

explicit SharedPtr(UnqPtr<T> p);

SharedPtr(const SharedPtr& other);

SharedPtr& operator=(const SharedPtr& other);

~SharedPtr();

T* get() const;

bool empty() const;

T* operator->() const;
T& operator*() const;
};

template <typename T>
SharedPtr<T>::SharedPtr() :
    ptr(UnqPtr<T>()), counter(new int(0)) {}

template <typename T>
SharedPtr<T>::SharedPtr(UnqPtr<T> p) :
    ptr(p), counter(new int(1)) {}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) :
    ptr(other.ptr), counter(other.counter) {
        (*counter)++;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    if (this != &other) {
        if (ptr) {
            (*counter)--;
            if ((*counter) == 0) {
                delete counter;
            }
        }
        ptr = other.ptr;
        counter = other.counter;
        if (ptr) {
            (*counter)++;
        }
    }
    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (ptr) {
        (*counter)--;
        if ((*counter) == 0) {
            delete counter;
        }
    }
}

template <typename T>
T* SharedPtr<T>::get() const {
    return ptr.get();
}

template <typename T>
bool SharedPtr<T>::empty() const {
    return ptr.empty();
}

template <typename T>
T* SharedPtr<T>::operator->() const {
    return ptr.operator->();
}

template <typename T>
T& SharedPtr<T>::operator*() const {
    return ptr.operator*();
}

#endif //MEPHI_LAB_SHRDPTR_H
