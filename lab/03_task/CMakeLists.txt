cmake_minimum_required(VERSION 3.16)
project(task3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
)

FetchContent_MakeAvailable(benchmark)

add_executable(task3
        main.cpp
        src/benchmarks.cpp
)

target_include_directories(task3 PRIVATE include)

target_link_libraries(task3
        benchmark::benchmark
        benchmark::benchmark_main
)