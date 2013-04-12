cmake_minimum_required (VERSION 2.8)

project(c++11examples)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

if(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)


add_executable(nullptr ${SRC_DIR}/nullptr.cpp)
add_executable(auto ${SRC_DIR}/auto.cpp)
