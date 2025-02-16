cmake_minimum_required(VERSION 3.5)
project(Linserver)

find_package(Threads REQUIRED)
include_directories(${CMAKE_THREAD_INCLUDE_DIRS})

add_executable(Linserver LinServer.cpp)
target_link_libraries( Linserver Threads::Threads)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(
    Linserver PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
