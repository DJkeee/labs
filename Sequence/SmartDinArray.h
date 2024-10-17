#ifndef SMARTDINARRAY_H
#define SMARTDINARRAY_H
#include "../Pointers/UnqPtr.h"

   template<typename T>
class SmartDynamicArray {
private:
    T* m_data;
    int m_size = 0;
    int m_capacity = 0;

    void copyOfMemory(int newCapacity) {
        if (newCapacity <= m_capacity) {
            return;
        }

        T* newData = new T[newCapacity];

        for (int i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }

        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

public:
    SmartDynamicArray() : m_data(nullptr), m_size(0), m_capacity(0) {}

    SmartDynamicArray(int size) : m_size(size), m_capacity(size) {
        if (size <= 0) throw std::length_error("Negative size is not allowed.");
        m_data = new T[size];
    }

    SmartDynamicArray(T* data, int size) : m_size(size), m_capacity(size) {
        if (size <= 0) throw std::length_error("Negative size is not allowed.");
        m_data = new T[size];
        for (int i = 0; i < size; i++) {
            m_data[i] = data[i];
        }
    }

    SmartDynamicArray(const SmartDynamicArray<T>& array) : m_size(array.m_size), m_capacity(array.m_capacity) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = array.m_data[i];
        }
    }

    virtual ~SmartDynamicArray() {
        delete[] m_data;
    }

    T get(int index) const {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        return m_data[index];
    }

    int getSize() const {
        return m_size;
    }

    void set(const T& value, int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range.");
        }
        m_data[index] = value;
    }

    void resize(int newSize) {
        if (newSize <= 0) {
            throw std::length_error("Negative size is not allowed.");
        }

        if (newSize > m_capacity) {
            copyOfMemory(newSize * 2);
        }

        m_size = newSize;
    }

    void append(const T& value) {
        copyOfMemory(m_size + 1);
        m_data[m_size - 1] = value;
        m_size++; // Increase size
    }

    bool operator==(const SmartDynamicArray<T>& arr) const {
        if (m_size != arr.m_size) {
            return false;
        }
        for (int i = 0; i < m_size; i++) {
            if (get(i) != arr.get(i)) {
                return false;
            }
        }
        return true;
    }

    SmartDynamicArray<T>& operator=(const SmartDynamicArray<T>& array) {
        if (this != &array) {
            delete[] m_data;
            m_size = array.m_size;
            m_capacity = array.m_capacity;
            m_data = new T[m_capacity];
            for (int i = 0; i < m_size; i++) {
                m_data[i] = array.m_data[i];
            }
        }
        return *this;
    }
};


#endif //SMARTDINARRAY_H
