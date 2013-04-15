cmake_minimum_required (VERSION 2.8)

project(boostNet)

find_package( Boost 1.49 COMPONENTS thread system REQUIRED )

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../../include)

include_directories( ${Boost_INCLUDE_DIRS} ${INCLUDE_DIR})

set(SRC_DIR ${PROJECT_SOURCE_DIR})

set(SOURCES
    ${SRC_DIR}/ConsoleApplication.cpp
    ${SRC_DIR}/User.cpp
    ${SRC_DIR}/main.cpp
)

add_library(boostNet SHARED ${SRC_DIR}/BoostNet.cpp)

add_executable(boostNetClient ${SOURCES})
target_link_libraries( boostNetClient boostNet ${Boost_LIBRARIES} )
