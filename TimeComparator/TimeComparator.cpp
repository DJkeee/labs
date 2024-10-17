#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include "../Sequence/ArraySequence.h"
#include "../Sequence/ListSequence.h"
#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include "../Sequence/ArraySequence.h"
#include "../Sequence/ListSequence.h"


class TimeComparator {
public:
    template<typename Clock = std::chrono::high_resolution_clock>
    auto timeSpent(const typename Clock::time_point& start, const typename Clock::time_point& end) const -> std::chrono::milliseconds {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    void out(const std::chrono::milliseconds& elapsed, const std::string& dataStructureName) const {
        std::cout << "Время для " << dataStructureName << ": " << elapsed.count() << " мс\n";
    }

    void compareVectorAndArraySeq() {
        // Генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 100);

        // Измерение времени для std::vector
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> vec;
        for (int i = 0; i < 100000000; ++i) {
            vec.push_back(distrib(gen));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_vector = timeSpent(start, end);
        out(elapsed_vector, "std::vector");

        // Измерение времени для ArraySequence
        start = std::chrono::high_resolution_clock::now();
        ArraySequence<int> arraySeq;
        for (int i = 0; i < 100000000; ++i) {
            arraySeq.append(distrib(gen));
        }
        end = std::chrono::high_resolution_clock::now();
        auto elapsed_arraySeq = timeSpent(start, end);
        out(elapsed_arraySeq, "ArraySequence");
    }

    void compareListAndArrayList() {
        // Генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 100);

        for (int n = 1000; n <= 100000; n += 1000) {
            // Измерение времени для std::list
            auto start = std::chrono::high_resolution_clock::now();
            std::list<int> list;
            for (int i = 0; i < n; ++i) {
                list.push_back(distrib(gen));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed_list = timeSpent(start, end);
            out(elapsed_list, "std::list with size " + std::to_string(n));

            // Измерение времени для ArrayList
            start = std::chrono::high_resolution_clock::now();
            ListSequence<int> arrayList;
            for (int i = 0; i < n; ++i) {
                arrayList.append(distrib(gen));
            }
            end = std::chrono::high_resolution_clock::now();
            auto elapsed_arrayList = timeSpent(start, end);
            out(elapsed_arrayList, "ArrayList with size " + std::to_string(n));
        }
    }
};




