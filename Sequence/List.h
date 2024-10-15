#ifndef LAB2_3_LIST_H
#define LAB2_3_LIST_H

#include "Errors.h"
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T item;
        Node* next = nullptr;
    };

    Node* m_head = nullptr;
    int m_size = 0;

public:
    LinkedList() : m_size(0) {
    }

    explicit LinkedList(int size) : LinkedList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);


        Node** tmp = &(m_head);
        for (int i = 0; i < size; i++) {
            *tmp = new Node;
            (*tmp)->item = T();
            tmp = &((*tmp)->next);
        }
        m_size = size;
    }

    LinkedList(T* items, int size) : LinkedList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

        Node** ptr = &(m_head);
        for (int i = 0; i < size; i++) {
            *ptr = new Node;
            (*ptr)->item = items[i];
            ptr = &((*ptr)->next);
        }
        m_size = size;
    }

    LinkedList(const LinkedList<T>& list) {
        Node* ptr = list.m_head;
        Node** newPtr = &(m_head);

        for (int i = 0; i < list.m_size; i++, ptr = ptr->next) {
            *newPtr = new Node;
            (*newPtr)->item = ptr->item;
            newPtr = &((*newPtr)->next);
        }

        m_size = list.m_size;
    }

    virtual ~LinkedList() {
        Node* ptr = m_head;
        Node* next;
        while (ptr != nullptr) {
            next = ptr->next;
            delete ptr;
            ptr = next;
        }
        m_size = 0;
    }

    T getFirst() const {
        if (m_size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

        return m_head->item;
    }

    T getLast() const {
        if (m_size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

        Node* ptr = m_head;
        while (ptr->next != nullptr) ptr = ptr->next;
        return ptr->item;
    }

    T get(int index) const {
        if ((index < 0) || (index >= m_size)) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        Node* ptr; {
            int i = 0;
            for (i = 0, ptr = m_head; i < index; i++, ptr = ptr->next);
        }

        return ptr->item;
    }

    void set(const T& item, int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Node* ptr; {
            int i = 0;
            for (i = 0, ptr = m_head; i < index; i++, ptr = ptr->next);
        }

        ptr->item = item;
    }

    [[nodiscard]] int getSize() const { return m_size; }

    void append(const T& item) {
        Node** ptr = &(m_head);
        while (*ptr != nullptr) ptr = &((*ptr)->next);

        (*ptr) = new Node;
        (*ptr)->item = item;

        m_size++;
    }

    void prepend(const T& item) {
        Node* ptr = new Node{item, m_head};
        m_head = ptr;
        m_size++;
    }


    void removeAt(int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Node preHead = {m_head->item, m_head};
        Node* ptr; {
            int i = 0;
            for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
        }
        Node* tmp = ptr->next;
        ptr->next = ptr->next->next;
        delete tmp;

        m_head = preHead.next;
        m_size--;
    }


    void insertAt(const T& item, int index) {
        if (index < 0 || index > m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Node preHead = {m_head->item, m_head};
        Node* ptr; {
            int i = 0;
            for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
        }

        ptr->next = new Node{item, ptr->next};
        m_head = preHead.next;
        m_size++;
    }

    bool operator==(const LinkedList<T>& list) const {
        if (this->m_size != list.m_size) return false;

        for (int i = 0; i < m_size; i++) {
            if (this->get(i) != list.get(i)) return false;
        }

        return true;
    }
};


#endif //LAB2_3_LIST_H
