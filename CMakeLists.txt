cmake_minimum_required(VERSION 3.17)
project(container_performance)

set(CMAKE_CXX_STANDARD 17)

add_executable(container_performance main.cpp)

#I installed google benchmark globally
find_package(benchmark)
target_link_libraries(container_performance benchmark::benchmark)
