#include_directories(${THIRD_PARTY_DIR}/physx/physx/include)

add_library(PhysX INTERFACE)

target_include_directories(
    PhysX
    INTERFACE
    ${THIRD_PARTY_DIR}/physx/physx/include
)

target_link_libraries(
    MeowEngine
    PRIVATE
    PhysX
)

find_library(
    PHYSX_LIBRARY
    NAMES libPhysX_static_64.a
    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
)

find_library(
    PHYSX_COMMON_LIB
    NAMES libPhysXCommon_static_64.a
    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
)

find_library(
    PHYSX_FOUNDATION_LIB
    NAMES libPhysXFoundation_static_64.a
    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
)

find_library(
    PHYSX_EXTENSIONS_LIB
    NAMES libPhysXExtensions_static_64.a
    PATHS ${THIRD_PARTY_DIR}/physx/physx/bin/linux.x86_64/release
)

target_link_libraries(
    MeowEngine
    PUBLIC
    ${PHYSX_LIBRARY}
    ${PHYSX_COMMON_LIB}
    ${PHYSX_FOUNDATION_LIB}
    ${PHYSX_EXTENSIONS_LIB}
)