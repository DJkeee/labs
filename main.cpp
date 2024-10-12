#include <iostream>
#include <memory>
#include <vector>
#include "Sequence/ArraySequence.h"
#include "Pointers/UnqPtr.h"

using namespace std;



int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArraySequence<int> vec;
    UnqPtr<ArraySequence<int>> seq = makeUnq<ArraySequence<int>>(vec);
    for (int i = 0; i < 10; i++) {
        seq->append(i);
        seq->prepend(i);
    }
    cout << *seq << endl;
    }
