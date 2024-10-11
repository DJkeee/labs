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
    std::unique_ptr<DynamicArray<T> > m_array;

public:
    ArraySequence() {
        m_array = std::make_unique<DynamicArray<T> >();
    }

    ArraySequence(const ArraySequence<T>& seq) {
        m_array = std::make_unique<DynamicArray<T> >(*seq.m_array);
    }

    ArraySequence(DynamicArray<T>* array) {
        m_array = std::unique_ptr<DynamicArray<T> >(array);
    }

    ArraySequence(T* items, int size) {
        m_array = std::make_unique<DynamicArray<T> >(items, size);
    }

    ArraySequence(int size) {
        m_array = std::make_unique<DynamicArray<T> >(size);
    }

    virtual ~ArraySequence() = default; // no need to delete m_array, unique_ptr will handle it

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

    virtual void set(const T& item, int index) override {
        if (index < 0 || index >= this->getSize()) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        m_array->set(item, index);
    }

    void append(const T& item) override {
        m_array->resize(this->getSize() + 1);
        m_array->set(item, this->getSize() - 1);
    }

    virtual void prepend(const T& item) override {
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

    virtual void insertAt(const T& item, int index) override {
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

    friend std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& seq) {
        for (int i = 0; i < seq.getSize(); i++)
            os << seq.get(i) << " ";
        return os;
    }
};


#endif //LAB2_3_ARRAYSEQUENCE_H
