//
// Created by dmitry on 10/17/24.
//

#ifndef POSITIVEINPUT_H
#define POSITIVEINPUT_H

#include "Input.h"

#include <iostream>
#include <limits>


template<typename T>
class PositiveInput : public Input<T> {
public:
    T getInput() override {
        T value;
        while (true) {
            try {
                if (!(std::cin >> value)) {
                    throw std::invalid_argument("Invalid input");
                }
                if (std::cin.fail()) {
                    throw std::invalid_argument("Input operation failed");
                }
                if (validateInput(value)) {
                    return value;
                } else {
                    std::cout << "Please, enter the number of elements\n";
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    bool validateInput(const T& input) override {
        return input > 0;
    }
};

#endif //POSITIVEINPUT_H
