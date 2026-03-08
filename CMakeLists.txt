cmake_minimum_required(VERSION 3.10)
project(OV_VideoIngestionPoC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(OpenCV_DIR "D:/opencv/opencv/build")

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(video_ingestion main.cpp)
target_link_libraries(video_ingestion ${OpenCV_LIBS})