#include_directories(${THIRD_PARTY_DIR}/SDL/include)
#include_directories(${THIRD_PARTY_DIR}/SDL2_image)

find_package(SDL2 REQUIRED)

add_library(SDL_CUSTOM INTERFACE)

target_include_directories(
    SDL_CUSTOM
    INTERFACE
    ${THIRD_PARTY_DIR}/SDL/include
    ${THIRD_PARTY_DIR}/SDL2_image
)

#target_link_libraries(
#    MeowEngine
#    PRIVATE
#    SDL
#)

add_library(SDL_Framework INTERFACE)

target_link_options(SDL_Framework INTERFACE
    "-F${LIBRARY_DIR}/Frameworks"
)

target_link_libraries(SDL_Framework INTERFACE
    "-framework SDL2"
    "-framework SDL2_image"
)

target_link_libraries(
    MeowEngine
    PUBLIC
    ${SDL2_LIBRARIES} SDL_CUSTOM SDL_Framework
)

