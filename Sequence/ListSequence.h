#ifndef LAB2_3_LISTSEQUENCE_H
#define LAB2_3_LISTSEQUENCE_H

#include "../Sequence/Sequence.h"
#include "../Sequence/List.h"
#include <stdexcept>
#include <iostream>
#include "../Pointers/SmartPtr.h"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    SmartPtr<List<T> > m_list;

public:
    ListSequence()
        : m_list(new List<T>()) {
    }

    ListSequence(const ListSequence<T>& seq)
        : m_list(new List<T>(*seq.m_list)) {
    }

    explicit ListSequence(SmartPtr<List<T> > list)
        : m_list(list) {
    }

    ListSequence(T* items, int size)
        : m_list(new List<T>(items, size)) {
    }

    explicit ListSequence(int size)
        : m_list(new List<T>(size)) {
    }

    virtual ~ListSequence() {
    }

    void removeLast() {
        m_list->removeLast();
    }

    T getFirst() const override {
        return m_list->getFirst();
    }

    T getLast() const override {
        return m_list->getLast();
    }

    T get(int index) const override {
        return m_list->get(index);
    }

    int getSize() const override {
        return m_list->getSize();
    }

    void set(const T& item, int index) override {
        if (index < 0 || index >= this->getSize())
            throw std::out_of_range("Index out of range.");
        m_list->set(item, index);
    }

    void append(const T& item) override {
        m_list->append(item);
    }

    void removeFirst() {
        m_list->removeFirst();
    }

    void prepend(const T& item) override {
        m_list->prepend(item);
    }

    void insertAt(const T& item, int index) override {
        if (index < 0 || index > this->getSize())
            throw std::out_of_range("Index out of range.");
        m_list->insertAt(item, index);
    }

    friend std::ostream& operator<<(std::ostream& os, const ListSequence<T>& seq) {
        for (int i = 0; i < seq.getSize(); i++) {
            os << seq.get(i) << " ";
        }
        return os;
    }
};


#endif //LAB2_3_LISTSEQUENCE_H
