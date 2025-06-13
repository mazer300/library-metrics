#include "MetricsWriter.h"
#include <iostream>

// Кастомная метрика, добавленная для демонстрации масштабируемости кода (определяет максимальное значение)
class MaxMetric : public IMetric{
public:
    MaxMetric(const std::string& name_) : name(name_), maxx(std::numeric_limits<double>::lowest()){ }

    void add(double value_) override{
        std::lock_guard<std::mutex> lock(mutex_);
        maxx = std::max(maxx, value_);
    }
    double getAndReset() override{
        std::lock_guard<std::mutex> lock(mutex_);
        double result = maxx;
        maxx = 0;
        return result;
    }
    std::string getName() const override{
        return name;
    }
private:
    std::string name;
    double maxx;
    std::mutex mutex_;
};


int main(){
    MetricsCollector collector;

    // Стандартные метрики (по заданию)
    collector.registerMetric("CPU", MetricSignification::Average);
    collector.registerMetric("HTTP requests RPS", MetricSignification::Counter);

    // Кастомная метрика
    collector.registerCustomMetric("Max temp CPU", std::make_unique<MaxMetric>("Max temp CPU"));

    std::string filename = "metrics.log";
    MetricsWriter writer(collector, filename);


    std::cout << "Metrics collection complete!\n";
    return 0;
}