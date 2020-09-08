cmake_minimum_required(VERSION 3.13)

project(A_toe_into_madness CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Configuration types: ${CMAKE_CONFIGURATION_TYPES}")

set(OpenCV_DIR "/usr/local/Cellar/opencv/4.4.0_1/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} src/main.cpp src/VideoProcessor.cpp src/VideoProcessor.h)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

