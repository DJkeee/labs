//
// Created by 123 on 23.05.2024.
//

#ifndef LAB2_3_SEQUENCE_H
#define LAB2_3_SEQUENCE_H

template<typename T>
class Sequence {
public:
    virtual T getFirst() const = 0;

    virtual T getLast() const = 0;

    virtual T get(int index) const = 0;

    virtual int getSize() const = 0;

    virtual void set(const T &item, int index) = 0;

    virtual void append(const T &item) = 0;

    virtual void prepend(const T &item) = 0;

    virtual void insertAt(const T &item, int index) = 0;


    virtual bool operator==(const Sequence<T> &seq) const {
        if (this->getSize() != seq.getSize()) return false;

        for (int i = 0; i < this->getSize(); i++) {
            if (this->get(i) != seq.get(i)) return false;
        }

        return true;
    }
};


#endif //LAB2_3_SEQUENCE_H
