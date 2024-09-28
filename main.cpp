#include <iostream>
#include "Pointers/UnqPtr.h"

int main() {
    UnqPtr<int> ptr1(new int(5));
    std::cout << *ptr1;
    return 0;
}
