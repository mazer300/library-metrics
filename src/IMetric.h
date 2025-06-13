#pragma once
#include <string>

enum class MetricSignification{
    Average,
    Counter,
    Custom
};

class IMetric{
public:
    virtual ~IMetric() = default;
    virtual void add(double value) = 0;
    virtual double getAndReset() = 0;
    virtual std::string getName() const = 0;
};