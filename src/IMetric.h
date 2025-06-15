// IMetric.h
#pragma once
#include <string>

// Типы метрик
enum class MetricSignification {
    Average,  // Для вычисления среднего значения
    Counter,  // Для подсчета суммы значений
    Custom    // Пользовательский тип метрики
};

// Базовый интерфейс для всех метрик
class IMetric {
public:
    virtual ~IMetric() = default;
    virtual void add(double value) = 0;            // Добавление значения
    virtual double getAndReset() = 0;              // Получение и сброс значения
    virtual std::string getName() const = 0;       // Получение имени метрики
};