// AverageMetric.cpp
#include "AverageMetric.h"

// Конструктор
AverageMetric::AverageMetric(const std::string& _name) : name(_name), summ(0), count(0) {}

// Добавление нового значения в метрику
void AverageMetric::add(double value) {
    std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности
    summ += value;
    count++;
}

// Получение среднего значения и сброс накопленных данных
double AverageMetric::getAndReset() {
    std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности
    double average = count > 0 ? summ / count : 0;  // Вычисление среднего
    count = 0;      // Сброс счетчика
    summ = 0;       // Сброс суммы
    return average;
}

// Получение имени метрики
std::string AverageMetric::getName() const { return name; }