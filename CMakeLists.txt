cmake_minimum_required(VERSION 3.28)
project(computer_vision)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(computer_vision main.cpp)
target_link_libraries(computer_vision ${OpenCV_LIBS})
