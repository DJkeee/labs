//
// Created by dmitry on 10/17/24.
//

#ifndef POSITIVEINPUT_H
#define POSITIVEINPUT_H

#include "Input.h"

template<typename T>
class PositiveInput : public Input<T> {
public:
    T getInput() override {
        T value;
        std::cin >> value;

        while (!validateInput(value)) {
            std::cin >> value;
        }
        return value;
    }

    bool validateInput(const T& input) override {
        return std::cin.good() && input > 0;
    }
};

#endif //POSITIVEINPUT_H
