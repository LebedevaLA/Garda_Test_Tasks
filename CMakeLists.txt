cmake_minimum_required(VERSION 3.5)

project (Hello)

add_executable(Hello hello.cpp)
set_target_properties(
    Hello PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)