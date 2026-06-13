message(STATUS "Running Cmake")

cmake_minimum_required(VERSION 4.1)
project(MeowEngine)

#set(CMAKE_OSX_ARCHITECTURES "x86_64")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

include(${PROJECT_SOURCE_DIR}/installer/engine/Build.cmake)