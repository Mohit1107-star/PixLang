cmake_minimum_required(VERSION 3.14)
project(ImagePipeline)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImagePipeline src/main.cpp)

target_include_directories(ImagePipeline PRIVATE include)
