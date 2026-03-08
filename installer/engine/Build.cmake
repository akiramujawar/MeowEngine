message(STATUS "Selecting platform...")

set(BUILD_PLATFORM "console" CACHE STRING "Build type")

set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

# load engine
include(${CMAKE_CURRENT_LIST_DIR}/Engine.cmake)

# platform configs
message(STATUS "Selected build: ${BUILD_PLATFORM}")

if(BUILD_PLATFORM STREQUAL "console")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/platform/console)
elseif(BUILD_PLATFORM STREQUAL "mac")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Web.cmake)
elseif (BUILD_PLATFORM STREQUAL "web")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/Mac.cmake)
else()
    message(FATAL_ERROR "Unknown build type")
endif()