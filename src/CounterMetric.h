// CounterMetric.h
#pragma once
#include "IMetric.h"
#include <atomic>

// Класс для подсчета суммы значений метрики
class CounterMetric: public IMetric {
public:
    CounterMetric(const std::string& _name);  // Конструктор с именем метрики
    void add(double value) override;          // Добавление нового значения
    double getAndReset() override;            // Получение суммы и сброс
    std::string getName() const override;     // Получение имени метрики
    
private:
    std::string name;            // Название метрики
    std::atomic<int> value;      // Атомарное значение счетчика
};