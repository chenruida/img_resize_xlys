cmake_minimum_required(VERSION 3.21)
project(image_resize)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

set(LIBRARY_OUTPUT_PATH
        ${PROJECT_SOURCE_DIR}/lib
        )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)

add_library(${PROJECT_NAME} STATIC
        src/threshold_partition.cpp
        src/color_inversion.cpp
        src/contour_tools.cpp
        )

add_executable(main main.cpp)
target_link_libraries(main
        ${OpenCV_LIBS}
        ${PROJECT_NAME})

