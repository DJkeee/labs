//
// Created by dmitry on 10/17/24.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "TimeComparator/TimeComparator.cpp"
#include "Input/PositiveInput.h"
#include "Input/Input.h"

template<typename T>
class Menu {
private:
    TimeComparator<T> time_comparator;
    Input<T>* input;

public:
    void compareOfSequences() {
        std::cout << "Welcome to the Time Comparator!\n";
        std::cout << "Please enter the number of elements to test speed  ";
        input = new PositiveInput<int>;
        int size = input->getInput();
        time_comparator.TestOfArrays(size);
        time_comparator.TestOfLists(size);
    }
};


#endif //MENU_H
