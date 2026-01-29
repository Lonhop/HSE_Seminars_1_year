cmake_minimum_required(VERSION 3.16)
project(Task08)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Task08 main.cpp)

if(MSVC)
    target_compile_options(Task08 PRIVATE /W4 /permissive-)
else()
    target_compile_options(Task08 PRIVATE -Wall -Wextra -Wpedantic)
endif()