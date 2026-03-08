cmake_minimum_required(VERSION 4.1)

message(STATUS "Running Cmake")


project(MeowEngineTest2)

#set(CMAKE_OSX_ARCHITECTURES "x86_64")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

#add_subdirectory(installer/cmake)
include(${PROJECT_SOURCE_DIR}/installer/engine/Build.cmake)