//
// Created by 123 on 23.05.2024.
//

#ifndef LAB2_3_ARRAYSEQUENCE_H
#define LAB2_3_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DinamicArray.h"

template<typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> *m_array;

public:

    ArraySequence() {
        m_array = new DynamicArray<T>();
    }

    ArraySequence(const ArraySequence<T> &seq) {
        m_array = new DynamicArray<T>(*seq.m_array);
    }

    ArraySequence(DynamicArray<T> *array) {
        m_array = array;
    }

    ArraySequence(T *items, int size) {
        m_array = new DynamicArray<T>(items, size);
    }

    ArraySequence(int size) {
        m_array = new DynamicArray<T>(size);
    }

    virtual ~ArraySequence() {
        delete m_array;
    }

    virtual T getFirst() const override {
        return m_array->get(0);
    }

    virtual T getLast() const override {
        return m_array->get(this->getSize() - 1);
    }

    virtual T get(int index) const override {
        return m_array->get(index);
    }

    virtual int getSize() const override {
        return m_array->getSize();
    }

    virtual void set(const T &item, int index) override {
        if (index < 0 || index >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        m_array->set(item, index);
    }

    virtual ArraySequence<T> *getSubsequence(int start, int end) const override {
        if (start < 0 || start >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (end < 0 || end >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (start > end) throw std::logic_error("Think about your indexes bro\n");

        T subArray[end - start + 1];
        for (int i = 0; i < end - start + 1; i++)
            subArray[i] = this->m_array->get(i + start);

        ArraySequence<T> *subSequence = new ArraySequence<T>(subArray, end - start);

        return subSequence;
    }

    virtual void append(const T &item) override {
        m_array->resize(this->getSize() + 1);
        m_array->set(item, this->getSize() - 1);
    }


    virtual void prepend(const T &item) override {
        m_array->resize(this->getSize() + 1);
        T temp1 = m_array->get(0);
        T temp2;
        for (int i = 0; i < this->getSize() - 1; i++) {
            temp2 = temp1;
            temp1 = m_array->get(i + 1);
            m_array->set(temp2, i + 1);
        }
        m_array->set(item, 0);
    }


    virtual void insertAt(const T &item, int index) override {
        if (index < 0 || index > this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        m_array->resize(this->getSize() + 1);
        T temp1 = m_array->get(index);
        T temp2;
        for (int i = index; i < this->getSize() - 1; i++) {
            temp2 = temp1;
            temp1 = m_array->get(i + 1);
            m_array->set(temp2, i + 1);
        }
        m_array->set(item, index);
    }


    virtual ArraySequence<T> *concat(const Sequence<T> &seq) const override {
        DynamicArray<T> *array = new DynamicArray<T>(this->getSize() + seq.getSize());
        ArraySequence<T> *newSequence = new ArraySequence<T>(array);
        for (int i = 0; i < this->getSize(); i++)
            newSequence->set(this->get(i), i);

        for (int i = 0; i < seq.getSize(); i++)
            newSequence->set(seq.get(i), i + this->getSize());

        return newSequence;
    }

};

#endif //LAB2_3_ARRAYSEQUENCE_H
