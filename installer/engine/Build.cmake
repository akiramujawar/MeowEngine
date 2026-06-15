message(STATUS "Selecting platform...")

set(BUILD_PLATFORM "console" CACHE STRING "Build type")

#  ----- Set Architecture
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

# ----- Set Project Path if started from IDE
# this is auto set if Sandbox project builds
# we set engine/examples as project path (default)
if(NOT PROJECT_PATH)
    set(PROJECT_PATH ${PROJECT_SOURCE_DIR}/engine/examples)
endif()

# ---- Set Paths
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/libs/third-party)
set(MAIN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/engine/source)
set(INSTALLER_DIR ${PROJECT_SOURCE_DIR}/installer/engine/platform/${BUILD_PLATFORM})

# ----- Set the output folder for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/builds/${BUILD_PLATFORM})

add_executable(
    MeowStandalone

    ${MAIN_SOURCE_DIR}/main.mm
)

# ----- Build sandbox & engine
include(${CMAKE_CURRENT_LIST_DIR}/Engine.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Sandbox.cmake)

# ----- Link our Engine & Sandbox static libraries
target_link_libraries(
    MeowStandalone
    PRIVATE
    MeowEngine
)

target_link_libraries(
    MeowStandalone
    PRIVATE
    Sandbox
)

# ----- Platform Configs
message(STATUS "Selected build: ${BUILD_PLATFORM}")

if(BUILD_PLATFORM STREQUAL "console")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/console/Console.cmake)
elseif(BUILD_PLATFORM STREQUAL "web")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/web/Web.cmake)
elseif (BUILD_PLATFORM STREQUAL "mac")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/mac/Mac.cmake)
else()
    message(FATAL_ERROR "Unknown build type")
endif()