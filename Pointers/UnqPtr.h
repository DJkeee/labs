#ifndef MEPHI_LAB_UNQPTR_H
#define MEPHI_LAB_UNQPTR_H

template <typename T>
class UnqPtr {
private:
T* ptr;

public:
UnqPtr();

explicit UnqPtr(T* p);

UnqPtr(const UnqPtr& other) = delete;

UnqPtr& operator=(const UnqPtr& other) = delete;

T* get() const;

bool empty() const;

~UnqPtr();

UnqPtr<T> release();

T* operator->() const;

T& operator*() const;
};

//реализация методов
template <typename T>
UnqPtr<T>::UnqPtr() : ptr(nullptr) {}

template <typename T>
UnqPtr<T>::UnqPtr(T* p) : ptr(p) {}

template <typename T>
T* UnqPtr<T>::get() const {
    return ptr;
}

template <typename T>
bool UnqPtr<T>::empty() const {
    return ptr == nullptr;
}

template <typename T>
UnqPtr<T>::~UnqPtr() {
    delete ptr;
}

template <typename T>
UnqPtr<T> UnqPtr<T>::release() {
    T* tmp = ptr;
    ptr = nullptr;
    return UnqPtr<T>(tmp);
}

template <typename T>
T* UnqPtr<T>::operator->() const {
    return ptr;
}

template <typename T>
T& UnqPtr<T>::operator*() const {
    return *ptr;
}


#endif //MEPHI_LAB_UNQPTR_H
