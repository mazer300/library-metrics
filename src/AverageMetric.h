// AverageMetric.h
#pragma once
#include "IMetric.h"
#include <mutex>

// Класс для вычисления среднего значения метрики
class AverageMetric: public IMetric {
public:
    AverageMetric(const std::string& name);  // Конструктор с именем метрики
    void add(double value) override;         // Добавление нового значения
    double getAndReset() override;           // Получение среднего и сброс
    std::string getName() const override;    // Получение имени метрики
    
private:
    std::string name;    // Название метрики
    double summ;         // Сумма всех значений
    int count;           // Количество добавленных значений
    std::mutex mutex_;   // Мьютекс для потокобезопасности
};