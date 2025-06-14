// MetricsWriter.cpp
#include "MetricsWriter.h"
#include "AverageMetric.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>

// Конструктор
MetricsWriter::MetricsWriter(MetricsCollector& metricsCollector_, const std::string& filename_, 
                           std::chrono::milliseconds interval_) 
    : collector(metricsCollector_), filename(filename_), interval(interval_), running(true) {
    writer_thread = std::thread(&MetricsWriter::writeLoop, this);  // Запуск потока записи
}

// Деструктор
MetricsWriter::~MetricsWriter() {
    running = false;  // Остановка цикла записи
    if(writer_thread.joinable()) {
        writer_thread.join();  // Ожидание завершения потока
    }
}

// Основной цикл записи метрик
void MetricsWriter::writeLoop() {
    std::ofstream outfile(filename, std::ios::app);  // Открытие файла в режиме дополнения
    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open metrics file");
    }

    while (running) {
        auto start = std::chrono::steady_clock::now();
        
        // Формирование временной метки
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        
        std::tm tm;
        localtime_r(&time_t, &tm);
        
        std::ostringstream timestamp;
        timestamp << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "." 
                 << std::setfill('0') << std::setw(3) << ms.count();
        
        // Получение метрик с одновременным сбросом
        auto metrics = collector.getMetricsAndReset();
        
        // Формирование строки для записи
        std::ostringstream line;
        line << timestamp.str();
        
        for (const auto& [name, value] : metrics) {
            line << " \"" << name << "\" " << value;
        }
        
        line << "\n";
        
        // Запись в файл
        outfile << line.str();
        outfile.flush();
        
        // Ожидание до следующего интервала
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
        }
    }
}