#ifndef LAB2_3_DINAMICARRAY_H
#define LAB2_3_DINAMICARRAY_H

#include <stdexcept>
#include "Errors.h"

template<typename T>
class DynamicArray {
private:
    T* m_data = nullptr;
    int m_size = 0;
    int m_capacity = 0;

public:
    DynamicArray() : m_size(0), m_capacity(0) {
    }

    DynamicArray(int size) : m_size(size), m_capacity(size) {
        if (size <= 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);
        m_data = new T[size];
    }

    DynamicArray(T* data, int size) : m_size(size), m_capacity(size) {
        if (size <= 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

        m_data = new T[size];
        for (int i = 0; i < size; i++) {
            m_data[i] = data[i];
        }
    }

    DynamicArray(const DynamicArray<T> &array, int size) : m_size(size), m_capacity(size) {
        if (size <= 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

        if (size > array.m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        m_data = new T[size];
        for (int i = 0; i < size; i++) {
            m_data[i] = array.m_data[i];
        }
    }

    DynamicArray(const DynamicArray<T> &array) : m_size(array.m_size), m_capacity(array.m_capacity) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = array.m_data[i];
        }
    }

    virtual ~DynamicArray() {
        delete[] m_data;
        m_size = 0;
        m_capacity = 0;
    }

    T get(int index) const {
        if (index < 0 || index >= m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        return m_data[index];
    }

    int getSize() const {
        return m_size;
    }

    void set(const T &value, int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        }
        m_data[index] = value;
    }

    void resize(int size) {
        if (size <= 0) {
            throw std::length_error(NEGATIVE_SIZE_MESSAGE);
        }
        T* newData = new T[size];

        for (int i = 0; i < (m_size > size ? size : m_size); i++) {
            newData[i] = m_data[i];
        }

        delete[] m_data;
        m_data = newData;

        m_size = size;
        m_capacity = size;
    }

    bool operator==(const DynamicArray<T> &arr) const {
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

    DynamicArray<T>& operator=(const DynamicArray<T> &array) {
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

#endif //LAB2_3_DINAMICARRAY_H
