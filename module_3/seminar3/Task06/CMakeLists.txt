cmake_minimum_required(VERSION 3.16)
project(Task06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Task06 main.cpp)

if(MSVC)
    target_compile_options(Task06 PRIVATE /W4 /permissive-)
else()
    target_compile_options(Task06 PRIVATE -Wall -Wextra -Wpedantic)
endif()