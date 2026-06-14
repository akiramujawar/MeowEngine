#include_directories(${THIRD_PARTY_DIR}/glm)

add_library(GLM INTERFACE)

target_include_directories(
    GLM
    INTERFACE
    ${THIRD_PARTY_DIR}/glm
)

target_link_libraries(
    MeowEngine
    PUBLIC
    GLM
)