cmake_minimum_required(VERSION 3.6)
project(hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DoublyLinkedList.cpp Stack.cpp IDunnoWhyIShouldImplementTheseUselessAndDumbMethods.cpp)
add_executable(hw2 ${SOURCE_FILES})