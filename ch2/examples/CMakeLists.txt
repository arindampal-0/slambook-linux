cmake_minimum_required( VERSION 3.12 )
project( examples )

set(CMAKE_CXX_FLAGS "-std=c++20")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_BUILD_TYPE DEBUG )

# include_directories("/usr/include/eigen3")

add_executable(coordinateTransform coordinateTransform.cpp)

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(plotTrajectory plotTrajectory.cpp)
target_link_libraries(plotTrajectory ${Pangolin_LIBRARIES})

