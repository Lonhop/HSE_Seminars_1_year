cmake_minimum_required(VERSION 3.20)
project(task02 VERSION 1.0.0 LANGUAGES CXX)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if(UNIX AND NOT APPLE)  # Linux
    find_library(MATH_LIB m)
    if(MATH_LIB)
        set(EXTRA_LIBS ${MATH_LIB})
    endif()
elseif(APPLE)
elseif(WIN32)
endif()

add_executable(point_project
        main.cpp
        src/point.cpp
)

if(EXTRA_LIBS)
    target_link_libraries(point_project ${EXTRA_LIBS})
endif()

set_target_properties(point_project PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        OUTPUT_NAME "point_app"
)