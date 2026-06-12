cmake_minimum_required(VERSION 4.1)

# Set Paths
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/libs/third-party)
set(MAIN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/engine/source)
set(ASSETS ${PROJECT_SOURCE_DIR}/engine/assets)
set(INSTALLER_DIR ${PROJECT_SOURCE_DIR}/installer/platforms/console)
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/libs)
set(SETTINGS_DIR ${PROJECT_SOURCE_DIR}/engine/settings)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/engine/include)
set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/engine/tools)
set(EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/engine/examples)

# Set output directory for builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/builds/console)
#set(CMAKE_BUILD_RPATH "@loader_path/dependencies/Frameworks")
#set(CMAKE_INSTALL_RPATH "@loader_path/dependencies/Frameworks")

# Sources
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS
    ${MAIN_SOURCE_DIR}/*.cpp
)

file(GLOB_RECURSE M_SOURCES CONFIGURE_DEPENDS
    ${MAIN_SOURCE_DIR}/*.m
)

file(GLOB_RECURSE SETTINGS_SOURCES CONFIGURE_DEPENDS
    ${SETTINGS_DIR}/*.cpp
)

file(GLOB_RECURSE INCLUDE_SOURCES CONFIGURE_DEPENDS
    ${INCLUDE_DIR}/*.cpp
)

file(GLOB_RECURSE TOOLS_SOURCES CONFIGURE_DEPENDS
    ${TOOLS_DIR}/*.cpp
)

file(GLOB_RECURSE EXAMPLES_SOURCES CONFIGURE_DEPENDS
    ${EXAMPLES_DIR}/*.cpp
)

# Recursive include directories
set(ALL_INCLUDE_DIRS)

foreach(ROOT_DIR
    ${MAIN_SOURCE_DIR}
    ${SETTINGS_DIR}
    ${INCLUDE_DIR}
    ${TOOLS_DIR}
    ${EXAMPLES_DIR}
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
add_executable(
    MeowEngine

    ${CPP_SOURCES}
    ${SETTINGS_SOURCES}
    ${INCLUDE_SOURCES}
    ${TOOLS_SOURCES}
    ${EXAMPLES_SOURCES}

    ${M_SOURCES}
    ${MAIN_SOURCE_DIR}/application/main.mm
)

target_include_directories(
    MeowEngine
    PRIVATE
    ${ALL_INCLUDE_DIRS}
)

# Run third-party cmake to link all the libraries
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/installer/engine/third-party
)

# Platform specific for apple (will come on this while working on web & windows) - painful stuff ehhhh
if(APPLE)
    target_link_libraries(
        MeowEngine
        PRIVATE
        "-framework AppKit"
        "-framework Foundation"
        "-framework UniformTypeIdentifiers"
        "-framework Cocoa"
    )

    # give the RPath for linking our custom dependencies/Frameworks
    set_target_properties(
        MeowEngine
        PROPERTIES
        BUILD_RPATH "@loader_path/dependencies/Frameworks"
    )

endif()

# Run external commands after building the MeowEngine
add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${INSTALLER_DIR}
    COMMAND ./cmake-post-build.sh -p console
)