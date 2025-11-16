cmake_minimum_required(VERSION 3.10)
project(ContainerBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(container_bench main.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(container_bench PRIVATE -O2)
endif()