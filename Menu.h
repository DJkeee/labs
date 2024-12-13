//
// Created by dmitry on 10/17/24.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Input/PositiveInput.h"
#include "Input/Input.h"

template<typename T>
class Menu {
private:
    Input<T>* input;

public:
    void compareOfSequences() {
        std::cout << "Welcome to the Time Comparator!\n";
        std::cout << "Please enter the number of elements to test speed  ";
        input = new PositiveInput<int>;
        int size = input->getInput();
    }
};


#endif //MENU_H
