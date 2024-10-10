#include <iostream>

#include "Sequence/Sequence.h"
#include "Sequence/ArraySequence.h"


int main() {


ArraySequence<int> vec;
Sequence<int>* seq = &vec;
    seq->append(1);
    seq->append(2);

    std::cout << vec << std::endl;

}
