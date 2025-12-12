cmake_minimum_required(VERSION 3.31)
project(MST_Parallel_Project)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(MST_Parallel_Project main.cpp
        kruksal.cpp
        kruskal.cpp
        kruskal.h)

if(OpenMP_CXX_FOUND)
    target_link_libraries(MST_Parallel_Project PUBLIC OpenMP::OpenMP_CXX)
endif()