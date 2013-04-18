# Language "C" is required for find_package(Threads).
project(gmock CXX C)
cmake_minimum_required(VERSION 2.6.2)

# Adds Google Mock's and Google Test's header directories to the search path.
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include")

set(gtest_src_dir ${PROJECT_SOURCE_DIR}/src)
set(gmock_src_dir ${PROJECT_SOURCE_DIR}/src)
########################################################################
#
# Defines the gmock & gmock_main libraries.  User tests should link
# with one of them.

# Google Mock libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that Google Mock can be compiled by
# a user aggressive about warnings.
add_library(gmock
            "${gtest_src_dir}/gtest-all.cc"
            "${gmock_src_dir}/gmock-all.cc")

add_library(gmock_main
            "${gtest_src_dir}/gtest-all.cc"
            "${gmock_src_dir}/gmock-all.cc"
            "${gmock_src_dir}/gmock_main.cc")
