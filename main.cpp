#include <iostream>
#include <memory>

#include "Pointers/ShrdPtr.h"
#include "Sequence/ArraySequence.h"

using namespace std;

int main() {
    int a = 5;
    ArraySequence<int> vec;
    Sequence<int>* seq = &vec;
    seq->append(10);
    seq->append(20);
    cout << vec;
}
