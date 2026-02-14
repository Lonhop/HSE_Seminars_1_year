cmake_minimum_required(VERSION 3.20)
project(SharedPtrTask)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(shared_ptr_task
        src/shared_ptr.cpp
        main.cpp
)

target_include_directories(shared_ptr_task PRIVATE include)

