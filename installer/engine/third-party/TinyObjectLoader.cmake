#include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)

add_library(TinyObjectLoader INTERFACE)

target_include_directories(
    TinyObjectLoader
    INTERFACE
    ${THIRD_PARTY_DIR}/tiny-obj-loader
)

target_link_libraries(
    MeowEngine
    PRIVATE
    TinyObjectLoader
)