cmake_minimum_required(VERSION 3.21)
project(image_resize)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_resize main.cpp image_resize.cpp image_resize.h)


target_link_libraries(image_resize ${OpenCV_LIBS})

