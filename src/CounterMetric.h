#pragma once
#include "IMetric.h"
#include <atomic>

class CounterMetric: public IMetric{
public:
    CounterMetric(const std::string& _name);
    void add(double value) override;
    double getAndReset() override;
    std::string getName() const override;
private:
    std::string name;
    std::atomic<int> value;
};