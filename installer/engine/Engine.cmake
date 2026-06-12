cmake_minimum_required(VERSION 4.1)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/libs/third-party)
set(MAIN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/engine/source)
set(ASSETS ${PROJECT_SOURCE_DIR}/engine/assets)
set(INSTALLER_DIR ${PROJECT_SOURCE_DIR}/installer/platforms/console)
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/libs)
set(SETTINGS_DIR ${PROJECT_SOURCE_DIR}/engine/settings)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/engine/include)
set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/engine/tools)
set(EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/engine/examples)

#find_package(OpenCL REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(SDL2 REQUIRED)

#
# Sources
#

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

#
# Recursive include directories
#

set(ALL_INCLUDE_DIRS)

#include_directories(${THIRD_PARTY_DIR}/SDL/include)
#include_directories(${THIRD_PARTY_DIR}/glm)
#include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)
#include_directories(${THIRD_PARTY_DIR}/SDL2_image)
#include_directories(${THIRD_PARTY_DIR}/magic-enum/include/magic_enum)
#include_directories(${THIRD_PARTY_DIR}/concurrentqueue)
#include_directories(${THIRD_PARTY_DIR}/imgui)
#include_directories(${THIRD_PARTY_DIR}/imgui/backends)
#include_directories(${THIRD_PARTY_DIR}/tracy/public/tracy)
#include_directories(${THIRD_PARTY_DIR}/entt/single_include/entt)
#include_directories(${THIRD_PARTY_DIR}/physx/physx/include)
#include_directories(${THIRD_PARTY_DIR}/nativefiledialog/src/include)

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

#
# Tracy
#

#add_library(
#    TracyClient STATIC
#    ${THIRD_PARTY_DIR}/tracy/public/TracyClient.cpp
#    ${THIRD_PARTY_DIR}/tracy/public/tracy/TracyOpenCL.hpp
#)
#
#target_compile_definitions(
#    TracyClient
#    PUBLIC
#    TRACY_ENABLE=1
#)

#
# Native File Dialog
#

#add_subdirectory(
#    ${THIRD_PARTY_DIR}/nativefiledialog
#    ${CMAKE_BINARY_DIR}/nativefiledialog-build
#)



#
# PhysX
#

#find_library(
#    PHYSX_LIBRARY
#    NAMES libPhysX_static_64.a
#    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
#)
#
#find_library(
#    PHYSX_COMMON_LIB
#    NAMES libPhysXCommon_static_64.a
#    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
#)
#
#find_library(
#    PHYSX_FOUNDATION_LIB
#    NAMES libPhysXFoundation_static_64.a
#    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
#)
#
#find_library(
#    PHYSX_EXTENSIONS_LIB
#    NAMES libPhysXExtensions_static_64.a
#    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
#)

#
# Executable
#

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

add_subdirectory(
    ${PROJECT_SOURCE_DIR}/installer/engine/third-party
)

#target_link_libraries(
#    MeowEngine
#    PUBLIC
#    OpenCL::OpenCL
#    TracyClient
#    ${CMAKE_DL_LIBS}
#)

#target_link_libraries(
#    MeowEngine
#    PUBLIC
##    ${SDL2_LIBRARIES}
#    ${OPENGL_LIBRARIES}
#)

#target_link_libraries(
#    MeowEngine
#    PRIVATE
#    nfd
#)

#target_link_libraries(
#    MeowEngine
#    PUBLIC
#    ${PHYSX_LIBRARY}
#    ${PHYSX_COMMON_LIB}
#    ${PHYSX_FOUNDATION_LIB}
#    ${PHYSX_EXTENSIONS_LIB}
#)

#target_link_libraries(
#    MeowEngine
#    PRIVATE
#    ImGui
#)

if(APPLE)
    target_link_libraries(
        MeowEngine
        PRIVATE
        "-framework AppKit"
        "-framework Foundation"
        "-framework UniformTypeIdentifiers"
        "-framework Cocoa"
    )

#    message(${SDL_LINK_FLAGS})
#    message(STATUS "SDL_LINK_FLAGS = '${SDL_LINK_FLAGS}'")
#    set_target_properties(
#        MeowEngine
#        PROPERTIES
#        LINK_FLAGS
#        "-F${LIBRARY_DIR}/Frameworks -framework OpenGL"
#    )
endif()

add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${INSTALLER_DIR}
    COMMAND ./cmake-post-build.sh -p console
)