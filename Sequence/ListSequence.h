#ifndef LAB2_3_LISTSEQUENCE_H
#define LAB2_3_LISTSEQUENCE_H

#include "../Pointers/UnqPtr.h"
#include "../Sequence/Sequence.h"
#include "SmartList.h"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    SmartList<T>* m_list;

public:
    // Default constructor
    ListSequence() : m_list(new SmartList<T>()) {
    }

    ListSequence(const ListSequence<T>& seq)
        : m_list(new SmartList<T>(*seq.m_list)) {
    }

    explicit ListSequence(SmartList<T>* list)
        : m_list(list) {
    }

    ListSequence(T* items, int size)
        : m_list(new SmartList<T>(items, size)) {
    }

    explicit ListSequence(int size)
        : m_list(new SmartList<T>(size)) {
    }

    virtual ~ListSequence() {
        delete m_list;
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
        m_list->set(item, index);
    }

    void append(const T& item) override {
        m_list->append(item);
    }

    void prepend(const T& item) override {
        m_list->prepend(item);
    }

    void insertAt(const T& item, int index) override {
        m_list->insertAt(item, index);
    }

    friend std::ostream& operator<<(std::ostream& os, const ListSequence<T>& seq) {
        for (int i = 0; i < seq.getSize(); i++)
            os << seq.get(i) << " ";
        return os;
    }
};


#endif //LAB2_3_LISTSEQUENCE_H
