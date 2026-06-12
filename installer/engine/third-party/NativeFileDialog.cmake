#include_directories(${THIRD_PARTY_DIR}/nativefiledialog/src/include)

#add_library(TinyObjectLoader INTERFACE)
#
#target_include_directories(
#    TinyObjectLoader
#    INTERFACE
#    ${THIRD_PARTY_DIR}/tiny-obj-loader
#)
#
#target_link_libraries(
#    MeowEngine
#    PRIVATE
#    TinyObjectLoader
#)

add_subdirectory(
    ${THIRD_PARTY_DIR}/nativefiledialog
    ${CMAKE_BINARY_DIR}/nativefiledialog-build
)

target_link_libraries(
    MeowEngine
    PRIVATE
    nfd
)