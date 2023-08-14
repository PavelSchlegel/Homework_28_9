cmake_minimum_required(VERSION 3.12)
project(Homework_28_9)

add_executable(Homework_28_9 main.cpp merge_sort.cpp)

set_target_properties(Homework_28_9
        PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)