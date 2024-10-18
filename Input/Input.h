//
// Created by dmitry on 10/17/24.
//

#ifndef INPUT_H
#define INPUT_H

template<typename T>
class Input {
public:
    virtual ~Input() {
    }

    virtual T getInput() = 0;

    virtual bool validateInput(const T& input) = 0;
};
#endif //INPUT_H
