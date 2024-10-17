#ifndef LAB2_3_LIST_H
#define LAB2_3_LIST_H

#include "Errors.h"
#include <stdexcept>

template<typename T>
class RawList {
private:
    struct Node {
        T item;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    int m_size = 0;

public:
    RawList() = default;

    explicit RawList(int size) : RawList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);
        for (int i = 0; i < size; i++) {
            append(T());
        }
    }

    RawList(T* items, int size) : RawList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);
        for (int i = 0; i < size; i++) {
            append(items[i]);
        }
    }

    RawList(const RawList<T>& list) : RawList() {
        for (int i = 0; i < list.m_size; i++) {
            append(list.get(i));
        }
    }

    ~RawList() {
        Node* ptr = m_head;
        Node* next;
        while (ptr != nullptr) {
            next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }

    T getFirst() const {
        if (m_size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        return m_head->item;
    }

    T getLast() const {
        if (m_size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        return m_tail->item;
    }

    T get(int index) const {
        if ((index < 0) || (index >= m_size)) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Node* ptr = m_head;
        for (int i = 0; i < index; i++) ptr = ptr->next;
        return ptr->item;
    }

    void set(const T& item, int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Node* ptr = m_head;
        for (int i = 0; i < index; i++) ptr = ptr->next;
        ptr->item = item;
    }

    int getSize() const { return m_size; }

    void append(const T& item) {
        Node* newNode = new Node{item, nullptr, m_tail};
        if (m_tail != nullptr) {
            m_tail->next = newNode;
        } else {
            m_head = newNode;
        }
        m_tail = newNode;
        m_size++;
    }

    void prepend(const T& item) {
        Node* newNode = new Node{item, m_head, nullptr};
        if (m_head != nullptr) {
            m_head->prev = newNode;
        } else {
            m_tail = newNode;
        }
        m_head = newNode;
        m_size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Node* ptr = m_head;
        if (index == 0) {
            m_head = ptr->next;
            if (m_head != nullptr) {
                m_head->prev = nullptr;
            } else {
                m_tail = nullptr;
            }
        } else {
            for (int i = 0; i < index - 1; i++) ptr = ptr->next;
            Node* next = ptr->next;
            ptr->next = next->next;
            if (next->next != nullptr) {
                next->next->prev = ptr;
            } else {
                m_tail = ptr;
            }
            delete next;
        }
        m_size--;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > m_size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (index == 0) {
            prepend(item);
        } else if (index == m_size) {
            append(item);
        } else {
            Node* ptr = m_head;
            for (int i = 0; i < index - 1; i++) ptr = ptr->next;
            Node* newNode = new Node{item, ptr->next, ptr};
            ptr->next->prev = newNode;
            ptr->next = newNode;
            m_size++;
        }
    }

    bool operator==(const RawList<T>& list) const {
        if (m_size != list.m_size) return false;
        Node* ptr1 = m_head;
        Node* ptr2 = list.m_head;
        for (int i = 0; i < m_size; i++) {
            if (ptr1->data != ptr2->data) return false;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return true;
    }
};

#endif //LAB2_3_LIST_H
