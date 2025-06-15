// MetricsWriter.h
#pragma once
#include "MetricsCollector.h"
#include <chrono>
#include <thread>

// Класс для записи метрик в файл с заданным интервалом
class MetricsWriter {
public:
    // Конструктор с указанием коллектора, имени файла и интервала записи
    MetricsWriter(MetricsCollector& metricsCollector, const std::string& filename, 
                std::chrono::milliseconds interval = std::chrono::milliseconds(1000));
    
    ~MetricsWriter();  // Деструктор
    
private:
    void writeLoop();  // Основной цикл записи

    MetricsCollector& collector;  // Ссылка на коллектор метрик
    std::string filename;         // Имя файла для записи
    std::chrono::milliseconds interval;  // Интервал записи
    bool running;                 // Флаг работы потока
    std::thread writer_thread;    // Поток для записи
};