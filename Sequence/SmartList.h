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
        Node* next = nullptr; // Use raw pointer for next node
        Node* prev = nullptr; // Use raw pointer for previous node

        Node(const T& item) : item(item) {
        }
    };

    Node* m_head = nullptr; // Use raw pointer for head
    Node* m_tail = nullptr; // Use raw pointer for tail
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
            delete ptr; // Delete each node
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
            m_head = newNode; // Set head if the list is empty
        }
        m_tail = newNode; // Update tail
        m_size++;
    }

    void prepend(const T& item) {
        Node* newNode = new Node(item);
        if (m_head) {
            newNode->next = m_head; // Set new node's next to current head
            m_head->prev = newNode; // Set current head's prev to new node
        }
        m_head = newNode; // Update head
        if (!m_tail) {
            m_tail = newNode; // Update tail if list was empty
        }
        m_size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= m_size) throw std::out_of_range("Index out of range");
        if (index == 0) {
            m_head = m_head->next; // Move head
            if (m_head) {
                m_head->prev = nullptr;
            } else {
                m_tail = nullptr; // List is now empty
            }
        } else {
            Node* ptr = m_head;
            for (int i = 0; i < index - 1; i++) ptr = ptr->next;
            Node* toDelete = ptr->next;
            ptr->next = toDelete->next;
            if (ptr->next) {
                ptr->next->prev = ptr;
            } else {
                m_tail = ptr; // Update tail if removing last node
            }
            delete toDelete; // Delete the node
        }
        m_size--;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > m_size) throw std::out_of_range("Index out of range");


        if (index == 0) {
            prepend(item); // Insert at the beginning
        } else if (index == m_size) {
            append(item); // Insert at the end
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
