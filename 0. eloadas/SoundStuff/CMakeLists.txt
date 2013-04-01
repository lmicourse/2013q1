cmake_minimum_required (VERSION 2.8)

project(SoundStuff)

# http://www.cmake.org/Wiki/CMake/Tutorials/C++11Flags
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()
# MSVC does not require any special flags

set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(LIBDIR ${PROJECT_SOURCE_DIR}/lib)

include_directories( ${LIBDIR} )

set(COMMON_SOURCES
    ${SRCDIR}/morsetext.cpp
    ${SRCDIR}/SoundSample.cpp
    ${LIBDIR}/fft/fft.cpp
    ${LIBDIR}/fft/complex.cpp
)

add_executable(SoundStuff ${SRCDIR}/main.cpp ${COMMON_SOURCES})
add_executable(SoundTest  ${SRCDIR}/main-1.cpp ${COMMON_SOURCES})
