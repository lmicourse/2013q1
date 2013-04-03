cmake_minimum_required (VERSION 2.8)

project(SoundStuff)

# http://www.cmake.org/Wiki/CMake/Tutorials/C++11Flags
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

if(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()
# MSVC does not require any special flags

set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(LIBDIR ${PROJECT_SOURCE_DIR}/lib)

include_directories( ${LIBDIR} )

add_library(SoundStuffLib
    ${SRCDIR}/morsetext.cpp
    ${SRCDIR}/SoundSample.cpp
)

add_library(FFTLib
    ${LIBDIR}/fft/fft.cpp
    ${LIBDIR}/fft/complex.cpp
)

add_executable(SoundStuff ${SRCDIR}/main.cpp)
add_executable(SoundTest  ${SRCDIR}/main-1.cpp)

set(LIBS
    SoundStuffLib # Order matters!
    FFTLib
)

target_link_libraries(SoundStuff ${LIBS})
target_link_libraries(SoundTest ${LIBS})
