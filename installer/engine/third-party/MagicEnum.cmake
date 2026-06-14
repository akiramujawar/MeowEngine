#include_directories(${THIRD_PARTY_DIR}/magic-enum/include/magic_enum)

add_library(MagicEnum INTERFACE)

target_include_directories(
    MagicEnum
    INTERFACE
    ${THIRD_PARTY_DIR}/magic-enum/include/magic_enum
)

target_link_libraries(
    MeowEngine
    PUBLIC
    MagicEnum
)