// CounterMetric.cpp
#include "CounterMetric.h"

// Конструктор
CounterMetric::CounterMetric(const std::string& _name) : name(_name), value(0) {}

// Добавление нового значения в метрику
void CounterMetric::add(double value_) { 
    value += value_;  // Атомарная операция сложения
}

// Получение текущего значения и сброс счетчика
double CounterMetric::getAndReset() { 
    return value.exchange(0);  // Атомарный обмен с 0
}

// Получение имени метрики
std::string CounterMetric::getName() const { return name; }