#include_directories(${THIRD_PARTY_DIR}/entt/single_include/entt)

add_library(Entt INTERFACE)

target_include_directories(
    Entt
    INTERFACE
    ${THIRD_PARTY_DIR}/entt/single_include/entt
)

target_link_libraries(
    MeowEngine
    PUBLIC
    Entt
)