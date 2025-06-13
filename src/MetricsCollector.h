#pragma once
#include "CounterMetric.h"
#include <memory>
#include <vector>
#include <mutex>
#include <unordered_map>

class MetricsCollector{
public:
    void registerMetric(const std::string& name_metric, MetricSignification signification);
    void registerCustomMetric(const std::string& name_metric, std::unique_ptr<IMetric> metric);
    void addValue(std::string& name, double value);
    std::vector<std::pair<std::string, double>> getMetricsAndReset();
private:
    std::mutex mutex_;
    std::unordered_map<std::string, std::unique_ptr<IMetric>> metrics;
};