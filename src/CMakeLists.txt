cmake_minimum_required(VERSION 3.10)

project(LibraryMetrics)

set(CMAKE_CXX_STANDARD 17)

add_executable(LibraryMetrics
    main.cpp
    AverageMetric.cpp
    CounterMetric.cpp
    MetricsCollector.cpp
    MetricsWriter.cpp
)

target_include_directories(LibraryMetrics PUBLIC ${CMAKE_SOURCE_DIR})