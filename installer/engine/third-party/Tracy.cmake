#include_directories(${THIRD_PARTY_DIR}/tracy/public/tracy)



add_library(
    TracyClient STATIC
    ${THIRD_PARTY_DIR}/tracy/public/TracyClient.cpp
    ${THIRD_PARTY_DIR}/tracy/public/tracy/TracyOpenCL.hpp
)

target_include_directories(
    TracyClient
    PUBLIC
    ${THIRD_PARTY_DIR}/tracy/public/tracy
)

target_compile_definitions(
    TracyClient
    PUBLIC
    TRACY_ENABLE=1
)

target_link_libraries(
    MeowEngine
    PUBLIC
    OpenCL::OpenCL
    TracyClient
    ${CMAKE_DL_LIBS}
)