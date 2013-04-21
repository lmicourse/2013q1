cmake_minimum_required (VERSION 2.8)

project(unittest)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

if(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

find_package(Threads REQUIRED)

set(GMOCK_DIR "${PROJECT_SOURCE_DIR}/external")

add_library(gmock STATIC IMPORTED)
set_property(TARGET gmock PROPERTY IMPORTED_LOCATION "${GMOCK_DIR}/lib/libgmock.a")
add_library(gmock_main STATIC IMPORTED)
set_property(TARGET gmock_main PROPERTY IMPORTED_LOCATION "${GMOCK_DIR}/lib/libgmock_main.a")

include_directories("${GMOCK_DIR}/include")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_executable(simpleTest "${SRC_DIR}/simpleTest.cpp")
target_link_libraries(simpleTest gmock_main ${CMAKE_THREAD_LIBS_INIT} )

add_executable(optionsTest "${SRC_DIR}/optionsTest.cpp" "${SRC_DIR}/optionsFixtureTest.cpp" "${SRC_DIR}/Options.cpp")
target_link_libraries(optionsTest gmock_main ${CMAKE_THREAD_LIBS_INIT} )
