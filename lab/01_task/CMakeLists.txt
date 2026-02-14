cmake_minimum_required(VERSION 3.20)
project(UniquePtrTask)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(unique_ptr_task
        src/unique_ptr.cpp
        main.cpp
)

target_include_directories(unique_ptr_task PRIVATE include)

