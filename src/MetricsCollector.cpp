#include "MetricsCollector.h"
#include "AverageMetric.h"
#include "CounterMetric.h"

void MetricsCollector::registerMetric(const std::string& name_metric, MetricSignification signification){
    std::lock_guard<std::mutex> lock(mutex_);
    if(metrics.find(name_metric) != metrics.end()) return ;

    switch (signification){
    case MetricSignification::Counter:
        metrics[name_metric] = std::make_unique<CounterMetric>(name_metric);
        break;
    case MetricSignification::Average:
        metrics[name_metric] = std::make_unique<AverageMetric>(name_metric);
        break;
    default:
        throw std::invalid_argument("Invalid metric signification");
    }
}

void MetricsCollector::registerCustomMetric(const std::string& name_metric, std::unique_ptr<IMetric> metric){
    std::lock_guard<std::mutex> lock(mutex_);
    metrics[name_metric] = std::move(metric);
}

void MetricsCollector::addValue(double value){
     std::lock_guard<std::mutex> lock(mutex_);
}

std::vector<std::pair<std::string, double>> MetricsCollector::getMetricsAndReset(){
    std::vector<std::pair<std::string, double>> result;
    std::lock_guard<std::mutex> lock(mutex_);

    for(auto& [name, metric] : metrics){
        result.emplace_back(name, metric -> getAndReset());
    }
    return result;
}