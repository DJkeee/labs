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
#include "../Sequence/DinamicArray.h"
#include "../Sequence/List.h"


template <typename T>
class TimeComparator {
public:
    TimeComparator() {}

    std::chrono::duration<double> timeDifference(std::chrono::high_resolution_clock::time_point start,
                                                  std::chrono::high_resolution_clock::time_point end) {
        return end - start;
    }

    void TestOfArrays(int size) {
        ArraySequence<T> arrSeq;
        DynamicArray<T> dynArr;
        std::vector<T> testData(size);

        for (int i = 0; i < size; ++i) {
            testData[i] = static_cast<T>(i);
        }

        auto startInsertArr = std::chrono::high_resolution_clock::now();
        for (const auto& item : testData) {
            arrSeq.append(item);
        }
        auto endInsertArr = std::chrono::high_resolution_clock::now();
        std::cout << "ArraySequence Insert Time: "
                  << timeDifference(startInsertArr, endInsertArr).count() << " seconds\n";

        auto startInsertDyn = std::chrono::high_resolution_clock::now();
        for (const auto& item : testData) {
            dynArr.append(item);
        }
        auto endInsertDyn = std::chrono::high_resolution_clock::now();
        std::cout << "DynamicArray Insert Time: "
                  << timeDifference(startInsertDyn, endInsertDyn).count() << " seconds\n";
    }

    void TestOfLists(int size) {
        ListSequence<T> listSeq;
        RawList<T> rawList;
        std::vector<T> testData(size);

        // Generate test data
        for (int i = 0; i < size; ++i) {
            testData[i] = static_cast<T>(i);
        }

        auto startInsertList = std::chrono::high_resolution_clock::now();
        for (const auto& item : testData) {
            listSeq.append(item);
        }
        auto endInsertList = std::chrono::high_resolution_clock::now();
        std::cout << "ListSequence Insert Time: "
                  << timeDifference(startInsertList, endInsertList).count() << " seconds\n";

        auto startInsertRaw = std::chrono::high_resolution_clock::now();
        for (const auto& item : testData) {
            rawList.append(item);
        }
        auto endInsertRaw = std::chrono::high_resolution_clock::now();
        std::cout << "RawList Insert Time: "
                  << timeDifference(startInsertRaw, endInsertRaw).count() << " seconds\n";
    }
};