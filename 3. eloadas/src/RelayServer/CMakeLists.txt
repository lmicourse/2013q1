cmake_minimum_required (VERSION 2.8)

project(RelayServer)

find_package( Boost 1.49 COMPONENTS thread system REQUIRED )

include_directories( ${Boost_INCLUDE_DIRS} )

set(SRC_DIR ${PROJECT_SOURCE_DIR})

set(SOURCES
    ${SRC_DIR}/Peer.cpp
    ${SRC_DIR}/RelayServer.cpp
    ${SRC_DIR}/main.cpp
)

add_executable(RelayServer ${SOURCES})
target_link_libraries( RelayServer ${Boost_LIBRARIES} )
