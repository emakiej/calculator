cmake_minimum_required(VERSION 2.8)

project(calculation_test)
file(GLOB_RECURSE libs_SRC "*.cpp" "*.hpp" "*.txt" "../src/*.cpp")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} ${libs_SRC})

include (ExternalProject)

target_link_libraries (${PROJECT_NAME} gtest gmock pthread)
set (gtest_disable_pthreads on)
