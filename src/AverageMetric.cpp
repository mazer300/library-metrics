#include "AverageMetric.h"

AverageMetric::AverageMetric(const std::string& _name) : name(_name), summ(0), count(0){}
void AverageMetric::add(double value) {
    std::lock_guard<std::mutex> lock(mutex_);
    summ+=value;
    count++;
}
double AverageMetric::getAndReset() {
    std::lock_guard<std::mutex> lock(mutex_);
    double average = count>0 ? summ/count : 0;
    count = 0;
    summ = 0;
    return average;
}
std::string AverageMetric::getName() const {return name;}