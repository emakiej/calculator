cmake_minimum_required(VERSION 2.8)

project(calculation)
file(GLOB libs_SRC "main.cpp" "src/*.hpp" "src/*.cpp")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} ${libs_SRC})


