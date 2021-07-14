cmake_minimum_required(VERSION 3.19)
project(curl_example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lcurl")

add_executable(curl_example main.cpp utils.cpp utils.h)
target_link_libraries(curl_example curl)