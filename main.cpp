#include <gtest/internal/gtest-string.h>

#include "Sequence/RBTree.cpp"
using namespace std;
int main() {
    RedBlackTree<int,string> tree;
    tree.insert(1,"aa");
    tree.insert(2,"bb");
    tree.insert(3,"cc");

    tree.print();

    return 0;
}
