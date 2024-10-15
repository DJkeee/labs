#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include "Mainwindow.h"

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

    // Метод для сравнения времени работы std::list и ArrayList
    void compareListAndArrayList() {
        // Генератор случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 100);

        // Данные для графика
        QVector<QPointF> listData, arrayListData;

        for (int n = 1000; n <= 100000; n += 1000) {
            // Измерение времени для std::list
            auto start = std::chrono::high_resolution_clock::now();
            std::list<int> list;
            for (int i = 0; i < n; ++i) {
                list.push_back(distrib(gen));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed_list = timeSpent(start, end);
            listData << QPointF(n, elapsed_list.count());

            // Измерение времени для ArrayList
            start = std::chrono::high_resolution_clock::now();
            ListSequence<int> arrayList;
            for (int i = 0; i < n; ++i) {
                arrayList.append(distrib(gen));
            }
            end = std::chrono::high_resolution_clock::now();
            auto elapsed_arrayList = timeSpent(start, end);
            arrayListData << QPointF(n, elapsed_arrayList.count());
        }

        // Создание графика
        QChart *chart = new QChart;
        chart->setTitle("Сравнение времени работы std::list и ArrayList");

        // Линии для std::list и ArrayList
        QLineSeries *listSeries = new QLineSeries;
        listSeries->setName("std::list");
        listSeries->append(listData);

        QLineSeries *arrayListSeries = new QLineSeries;
        arrayListSeries->setName("ArrayList");
        arrayListSeries->append(arrayListData);

        // Добавление линий на график
        chart->addSeries(listSeries);
        chart->addSeries(arrayListSeries);

        // Оси графика
        QValueAxis *xAxis = new QValueAxis;
        xAxis->setTitleText("Количество объектов");
        xAxis->setRange(0, 100000);
        chart->addAxis(xAxis, Qt::AlignBottom);
        listSeries->attachAxis(xAxis);
        arrayListSeries->attachAxis(xAxis);

        QValueAxis *yAxis = new QValueAxis;
        yAxis->setTitleText("Время (мс)");
        yAxis->setRange(0, 10000); // Настройте диапазон по необходимости
        chart->addAxis(yAxis, Qt::AlignLeft);
        listSeries->attachAxis(yAxis);
        arrayListSeries->attachAxis(yAxis);

        // Создание представления графика
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Запуск Qt-приложения
        QApplication app(argc, argv);
        chartView->show();
        return app.exec();
    }
};

int main(int argc, char *argv[]) {
    TimeComparator test;
    //test.compareVectorAndArraySeq();
    //test.compareListAndArrayList(); // Вызывает Qt приложение для графика

    return 0;
}


