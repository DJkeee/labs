#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "Sequence/ArraySequence.h"
#include "Pointers/UnqPtr.h"
#include "Sequence/ListSequence.h"

using namespace std;

int main() {
    ListSequence<int> vec;
    UnqPtr<ListSequence<int>> seq = makeUnq<ListSequence<int>>(vec);
    for (int i = 0; i < 10; i++) {
        seq->append(i);
        seq->prepend(i);
    }
    cout << *seq << endl;
    }
