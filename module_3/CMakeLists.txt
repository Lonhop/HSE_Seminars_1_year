cmake_minimum_required(VERSION 3.13)  # Minimum CMake version required
project(seminar2)                # Set your project name
set(CMAKE_CXX_STANDARD 20)             # ⭐ Enable C++20 standard (required for concepts)

# Set source files - adjust path if needed
set(SOURCE_FILES "seminar2/task 4.cpp"
    "seminar2/task 1.cpp")

# Create executable target
add_executable(seminar2_task4 ${SOURCE_FILES})