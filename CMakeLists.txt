cmake_minimum_required(VERSION 3.10)
project(task)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_CPPLINT "cpplint")

set(SOURCES main.cpp)

add_executable(task ${SOURCES})
