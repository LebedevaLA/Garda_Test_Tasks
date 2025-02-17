cmake_minimum_required(VERSION 3.5)
project(CalcServ)

find_package(Threads REQUIRED)
include_directories(${CMAKE_THREAD_INCLUDE_DIRS})

add_executable(CalcServ CalcServer.cpp)
target_link_libraries(CalcServ Threads::Threads)

set_target_properties(
    CalcServ PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
