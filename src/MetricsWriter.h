#pragma once
#include "MetricsCollector.h"
#include <chrono>
#include <thread>

class MetricsWriter{
public:
    MetricsWriter(MetricsCollector& metricsCollector, const std::string& filename, std::chrono::milliseconds interval = std::chrono::milliseconds(1));
    ~MetricsWriter();
private:
    void writeLoop();

    MetricsCollector& collector;
    std::string filename;
    std::chrono::milliseconds interval;
    bool running;
    std::thread writer_thread;
};