#include <iostream>
#include <memory>

#include "Pointers/ShrdPtr.h"
#include "Sequence/Sequence.h"
#include "Sequence/ArraySequence.h"

using namespace std;

int main() {
    int a = 5;
    ShrdPtr<int> ptr = makeShrd<int>(a); // Создаем объект ShrdPtr, ссылающийся на a
    std::cout << ptr.getCount() << std::endl; // Вывод: 1

    ShrdPtr<int> ptr2 = ptr; // Копирование ShrdPtr
    std::cout << ptr2.getCount() << std::endl; // Вывод: 2
}
