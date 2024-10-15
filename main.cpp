#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "Sequence/ArraySequence.h"
#include "Pointers/UnqPtr.h"
#include "Sequence/ListSequence.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Ваша реализация ArraySequence (предполагается, что она уже есть)

class TimeTest {
public:
    void vectorAndArraySeqTime() {
        // Генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 100);


        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> vec;
        for (int i = 0; i < 100000; ++i) {
            vec.push_back(distrib(gen));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_vector = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


        start = std::chrono::high_resolution_clock::now();
        ArraySequence<int> arraySeq;
        for (int i = 0; i < 100000; ++i) {
            arraySeq.append(distrib(gen));
        }
        end = std::chrono::high_resolution_clock::now();
        auto elapsed_arraySeq = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


        std::cout << "Время для std::vector: " << elapsed_vector.count() << " мс\n";
        std::cout << "Время для ArraySequence: " << elapsed_arraySeq.count() << " мс\n";
    }
};

int main() {
    TimeTest test;
    test.vectorAndArraySeqTime();

    return 0;
}
