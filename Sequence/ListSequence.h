#ifndef LAB2_3_LISTSEQUENCE_H
#define LAB2_3_LISTSEQUENCE_H


#include "Sequence.h"
#include "List.h"

template<typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> *m_list;
public:

    ListSequence() {
        m_list = new LinkedList<T>();
    }

    ListSequence(const ListSequence<T> &seq) {
        m_list = new LinkedList<T>(*seq.m_list);
    }

    ListSequence(LinkedList<T> *list) {
        m_list = list;
    }

    ListSequence(T *items, int size) {
        m_list = new LinkedList<T>(items, size);
    }

    ListSequence(int size) {
        m_list = new LinkedList<T>(size);
    }

    virtual ~ListSequence() {
        delete m_list;
    }

    virtual T getFirst() const override {
        return m_list->getFirst();
    }

    virtual T getLast() const override {
        return m_list->getLast();
    }

    virtual T get(int index) const override {
        return m_list->get(index);
    }

    virtual int getSize() const override {
        return m_list->getSize();
    }

    virtual ListSequence<T> *getSubsequence(int start, int end) const override {
        LinkedList<T> *subList = this->m_list->getSublist(start, end);
        ListSequence<T> *seq = new ListSequence<T>(subList);
        return seq;
    }

    virtual void set(const T &item, int index) override {
        m_list->set(item, index);
    }

    virtual void append(const T &item) override {
        m_list->append(item);
    }

    virtual void prepend(const T &item) override {
        m_list->prepend(item);
    }

    virtual void insertAt(const T &item, int index) override {
        m_list->insertAt(item, index);
    }

    virtual ListSequence<T> *concat(const Sequence <T> &seq) const override {
        ListSequence<T> *newSequence = new ListSequence<T>();

        for (int i = 0; i < this->getSize(); i++)
            newSequence->append(this->get(i));

        for (int i = 0; i < seq.getSize(); i++)
            newSequence->append(seq.get(i));

        return newSequence;
    }


};


#endif //LAB2_3_LISTSEQUENCE_H
