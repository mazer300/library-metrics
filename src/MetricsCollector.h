// MetricsCollector.h
#pragma once
#include "CounterMetric.h"
#include <memory>
#include <vector>
#include <mutex>
#include <unordered_map>

// Класс для сбора и управления метриками
class MetricsCollector {
public:
    // Регистрация новой метрики стандартного типа
    void registerMetric(const std::string& name_metric, MetricSignification signification);
    
    // Регистрация пользовательской метрики
    void registerCustomMetric(const std::string& name_metric, std::unique_ptr<IMetric> metric);
    
    // Добавление значения в метрику
    void addValue(const std::string& name, double value);
    
    // Получение всех метрик с одновременным сбросом их значений
    std::vector<std::pair<std::string, double>> getMetricsAndReset();
    
private:
    std::mutex mutex_;  // Мьютекс для потокобезопасности
    std::unordered_map<std::string, std::unique_ptr<IMetric>> metrics;  // Хранилище метрик
};