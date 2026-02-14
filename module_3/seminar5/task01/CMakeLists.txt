cmake_minimum_required(VERSION 3.20)
project(task01 VERSION 1.0.0)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create executable from source files
add_executable(calculator
        main.cpp
        src/calculator.cpp
)

# Set properties for the executable
set_target_properties(calculator PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)