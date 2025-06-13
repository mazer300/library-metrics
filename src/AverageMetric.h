#pragma once
#include "IMetric.h"
#include <mutex>

class AverageMetric: public IMetric{
public:
    AverageMetric(const std::string& name);
    void add(double value) override;
    double getAndReset() override;
    std::string getName() const override;
private:
    std::string name;
    double summ;
    int count;
    std::mutex mutex_;
};