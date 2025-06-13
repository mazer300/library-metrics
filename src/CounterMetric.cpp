#include "CounterMetric.h"

CounterMetric::CounterMetric(const std::string& _name) : name(_name), value(0){}
void CounterMetric::add(double value_) { value+=value_; } //value=value.fetch_add(value_)
double CounterMetric::getAndReset() { return value.exchange(0); }
std::string CounterMetric::getName() const { return name; }