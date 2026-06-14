cmake_minimum_required(VERSION 4.1)

# Set Paths
#set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/libs/third-party)
#set(MAIN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/engine/source)
##set(ASSETS ${PROJECT_SOURCE_DIR}/engine/assets)
#set(INSTALLER_DIR ${PROJECT_SOURCE_DIR}/installer/engine/platform/${BUILD_PLATFORM})
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/libs)
set(SETTINGS_DIR ${PROJECT_SOURCE_DIR}/engine/settings)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/engine/include)
set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/engine/tools)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/engine/tests)

## move this to Sandbox later
#if(NOT PROJECT_PATH)
#    set(PROJECT_PATH ${PROJECT_SOURCE_DIR}/engine/examples)
#endif()

# Set output directory for builds
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/builds/${BUILD_PLATFORM})
#set(CMAKE_BUILD_RPATH "@loader_path/dependencies/Frameworks")
#set(CMAKE_INSTALL_RPATH "@loader_path/dependencies/Frameworks")

message("directory-----------------------------------")
message(${INSTALLER_DIR})
#message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Sources
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS
    ${MAIN_SOURCE_DIR}/*.cpp
)

set(M_SOURCES)
if(APPLE AND NOT EMSCRIPTEN)
    file(GLOB_RECURSE M_SOURCES CONFIGURE_DEPENDS
        ${MAIN_SOURCE_DIR}/platform/backends/mac/*.m
    )
endif ()

file(GLOB_RECURSE SETTINGS_SOURCES CONFIGURE_DEPENDS
    ${SETTINGS_DIR}/*.cpp
)

file(GLOB_RECURSE INCLUDE_SOURCES CONFIGURE_DEPENDS
    ${INCLUDE_DIR}/*.cpp
)

file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    ${TOOLS_DIR}/*.cpp
)

file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS
    ${TESTS_DIR}/*.cpp
)

# Recursive include directories
set(ALL_INCLUDE_DIRS)

foreach(ROOT_DIR
    ${MAIN_SOURCE_DIR}
    ${SETTINGS_DIR}
    ${INCLUDE_DIR}
    ${TOOLS_DIR}
    ${TESTS_DIR}
)
    list(APPEND ALL_INCLUDE_DIRS ${ROOT_DIR})

    file(GLOB_RECURSE ROOT_ENTRIES CONFIGURE_DEPENDS
        "${ROOT_DIR}/*"
    )

    foreach(ENTRY ${ROOT_ENTRIES})
        get_filename_component(DIR "${ENTRY}" DIRECTORY)

        if(IS_DIRECTORY "${DIR}")
            list(APPEND ALL_INCLUDE_DIRS "${DIR}")
        endif()
    endforeach()
endforeach()

list(REMOVE_DUPLICATES ALL_INCLUDE_DIRS)

# Add our main engine executable & link it
add_library(
    MeowEngine STATIC

    ${CPP_SOURCES}
    ${SETTINGS_SOURCES}
    ${INCLUDE_SOURCES}
    ${TOOLS_SOURCES}
    ${TESTS_SOURCES}

    ${M_SOURCES}
)

target_include_directories(
    MeowEngine
    PUBLIC
    ${ALL_INCLUDE_DIRS}
)

# Run third-party cmake to link all the libraries
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/installer/engine/third-party
)