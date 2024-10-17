//
// Created by 123 on 23.05.2024.
//

#ifndef LAB2_3_ARRAYSEQUENCE_H
#define LAB2_3_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "SmartDinArray.h"
#include "../Pointers/UnqPtr.h"

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    SmartDynamicArray<T>* m_array;

public:
    ArraySequence() : m_array(new SmartDynamicArray<T>()) {
    }

    ArraySequence(const ArraySequence<T>& seq)
        : m_array(new SmartDynamicArray<T>(*seq.m_array)) {
    }

    ArraySequence(SmartDynamicArray<T>* array)
        : m_array(array) {
    }

    ArraySequence(T* items, int size)
        : m_array(new SmartDynamicArray<T>(items, size)) {
    }

    ArraySequence(int size)
        : m_array(new SmartDynamicArray<T>(size)) {
    }

    virtual ~ArraySequence() {
        delete m_array;
    }

    T getFirst() const override {
        return m_array->get(0);
    }


    T getLast() const override {
        return m_array->get(this->getSize() - 1);
    }


    T get(int index) const override {
        return m_array->get(index);
    }


    int getSize() const override {
        return m_array->getSize();
    }


    void set(const T& item, int index) override {
        if (index < 0 || index >= this->getSize()) throw std::out_of_range("Index out of range.");
        m_array->set(item, index);
    }


    void append(const T& item) override {
        m_array->resize(this->getSize() + 1);
        m_array->set(item, this->getSize() - 1);
    }

    void prepend(const T& item) override {
        m_array->resize(this->getSize() + 1);
        T temp1 = m_array->get(0);
        for (int i = 0; i < this->getSize() - 1; i++) {
            T temp2 = m_array->get(i + 1);
            m_array->set(temp1, i + 1);
            temp1 = temp2;
        }
        m_array->set(item, 0);
    }


    void insertAt(const T& item, int index) override {
        if (index < 0 || index > this->getSize()) throw std::out_of_range("Index out of range.");

        m_array->resize(this->getSize() + 1);
        T temp1 = m_array->get(index);
        for (int i = index; i < this->getSize() - 1; i++) {
            T temp2 = m_array->get(i + 1);
            m_array->set(temp1, i + 1);
            temp1 = temp2;
        }
        m_array->set(item, index);
    }


    friend std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& seq) {
        for (int i = 0; i < seq.getSize(); i++)
            os << seq.get(i) << " ";
        return os;
    }
};
#endif //LAB2_3_ARRAYSEQUENCE_H
