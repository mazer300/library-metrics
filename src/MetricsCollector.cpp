// MetricsCollector.cpp
#include "MetricsCollector.h"
#include "AverageMetric.h"
#include "CounterMetric.h"
#include <algorithm>

// Регистрация новой метрики стандартного типа
void MetricsCollector::registerMetric(const std::string& name_metric, MetricSignification signification){
    std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности
    if(metrics.find(name_metric) != metrics.end()) return ;  // Проверка на наличие метрики в карте

    // Добалвение новой метрики в карту
    switch (signification){
    case MetricSignification::Counter:  // Добавление в карту метрики-счётчика
        metrics[name_metric] = std::make_unique<CounterMetric>(name_metric);
        break;
    case MetricSignification::Average:  // Добавление в карту метрики-среднего
        metrics[name_metric] = std::make_unique<AverageMetric>(name_metric);
        break;
    default:
        throw std::invalid_argument("Invalid metric signification");
    }
}

// Регистрация пользовательской метрики
void MetricsCollector::registerCustomMetric(const std::string& name_metric, std::unique_ptr<IMetric> metric){
    std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности
    metrics[name_metric] = std::move(metric);  // Добавление в карту пользовательской метрики
}

// Добавление значения в метрику
void MetricsCollector::addValue(const std::string& name, double value){
     std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности
     auto it = metrics.find(name);  // Найти метрику
     if(it != metrics.end()){  // Проверить, что метрика есть
        it -> second -> add(value);  // Добавить значение в метрику
     }
}

// Получение всех метрик с одновременным сбросом их значений
std::vector<std::pair<std::string, double>> MetricsCollector::getMetricsAndReset(){
    std::vector<std::pair<std::string, double>> result; // Вектор с результатами метрик
    std::lock_guard<std::mutex> lock(mutex_);  // Блокировка для потокобезопасности

    // Запись и сбросс значений метрик
    for(auto& [name, metric] : metrics){
        result.emplace_back(name, metric -> getAndReset());
    }
    std::reverse(result.begin(),result.end());  // Разворот вектора для 
    return result;
}