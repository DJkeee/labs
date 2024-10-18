//
// Created by dmitry on 10/17/24.
//

#ifndef SMARTLIST_H
#define SMARTLIST_H

template<typename T>
class SmartList {
private:
    struct Node {
        T item;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& item) : item(item) {
        }
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    int m_size = 0;

public:
    SmartList() = default;

    explicit SmartList(int size) : SmartList() {
        if (size < 0) throw std::length_error("Negative size");
        for (int i = 0; i < size; i++) {
            append(T());
        }
    }

    SmartList(T* items, int size) : SmartList() {
        if (size < 0) throw std::length_error("Negative size");
        for (int i = 0; i < size; i++) {
            append(items[i]);
        }
    }

    SmartList(const SmartList<T>& list) : SmartList() {
        for (int i = 0; i < list.m_size; i++) {
            append(list.get(i));
        }
    }

    ~SmartList() {
        Node* ptr = m_head;
        while (ptr != nullptr) {
            Node* next = ptr->next;
            delete ptr;
            ptr = next;
        }
    }

    T getFirst() const {
        if (m_size == 0) throw std::length_error("Zero size");
        return m_head->item;
    }

    T getLast() const {
        if (m_size == 0) throw std::length_error("Zero size");
        return m_tail->item;
    }

    T get(int index) const {
        if ((index < 0) || (index >= m_size)) throw std::out_of_range("Index out of range");
        Node* ptr = m_head;
        for (int i = 0; i < index; i++) ptr = ptr->next;
        return ptr->item;
    }

    void set(const T& item, int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
        Node* ptr = m_head;
        for (int i = 0; i < index; i++) ptr = ptr->next;
        ptr->item = item;
    }

    int getSize() const { return m_size; }

    void append(const T& item) {
        Node* newNode = new Node(item);
        if (m_tail) {
            m_tail->next = newNode;
            newNode->prev = m_tail;
        } else {
            m_head = newNode;
        }
        m_tail = newNode;
        m_size++;
    }

    void prepend(const T& item) {
        Node* newNode = new Node(item);
        if (m_head) {
            newNode->next = m_head;
            m_head->prev = newNode;
        }
        m_head = newNode;
        if (!m_tail) {
            m_tail = newNode;
        }
        m_size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
        if (index == 0) {
            m_head = m_head->next;
            if (m_head) {
                m_head->prev = nullptr;
            } else {
                m_tail = nullptr;
            }
        } else {
            Node* ptr = m_head;
            for (int i = 0; i < index - 1; i++) ptr = ptr->next;
            Node* toDelete = ptr->next;
            ptr->next = toDelete->next;
            if (ptr->next) {
                ptr->next->prev = ptr;
            } else {
                m_tail = ptr;
            }
            delete toDelete;
        }
        m_size--;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > m_size) throw std::out_of_range("Index out of range");


        if (index == 0) {
            prepend(item);
        } else if (index == m_size) {
            append(item);
        } else {
            Node* newNode = new Node(item);
            Node* ptr = m_head;
            for (int i = 0; i < index - 1; i++) ptr = ptr->next;
            newNode->next = ptr->next;
            newNode->prev = ptr;
            ptr->next->prev = newNode;
            ptr->next = newNode;
            m_size++;
        }
    }
};

#endif //SMARTLIST_H
