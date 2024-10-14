cmake_minimum_required( VERSION 3.12 )
project( examples )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# include_directories("/usr/include/eigen3")

add_executable(coordinateTransform coordinateTransform.cpp)

