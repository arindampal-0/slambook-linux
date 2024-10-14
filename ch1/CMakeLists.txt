cmake_minimum_required( VERSION 3.22.1 )
project( HelloSLAM )

Set( CMAKE_BUILD_TYPE "Debug" )

add_library( hello_shared SHARED libHelloSLAM.cpp )

add_executable( helloSLAM helloSLAM.cpp )

add_executable( useHello useHello.cpp )
target_link_libraries( useHello hello_shared )
