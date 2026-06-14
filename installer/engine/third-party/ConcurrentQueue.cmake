#include_directories(${THIRD_PARTY_DIR}/concurrentqueue)

#target_include_directories(
#    MeowEngine
#    PUBLIC
#    ${THIRD_PARTY_DIR}/concurrentqueue
#)

add_library(ConcurrentQueue INTERFACE)

target_include_directories(
    ConcurrentQueue
    INTERFACE
    ${THIRD_PARTY_DIR}/concurrentqueue
)

#target_include_directories(
#    MeowEngine
#    PUBLIC
#    ${THIRD_PARTY_DIR}/concurrentqueue
#)

target_link_libraries(
    MeowEngine
    PUBLIC
    ConcurrentQueue
)