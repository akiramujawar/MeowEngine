
if(EMSCRIPTEN)
    include_directories(${THIRD_PARTY_DIR}/SDL/include)
    include_directories(${THIRD_PARTY_DIR}/SDL2_image)

    target_compile_options(MeowEngine PRIVATE
        "-sUSE_SDL=2"
        "-sUSE_SDL_IMAGE=2"
    )

    target_link_options(MeowEngine PRIVATE
        "-sUSE_SDL=2"
        -sUSE_SDL_IMAGE=2
        -sSDL2_IMAGE_FORMATS=['png','jpg']
    )
elseif (APPLE)
    add_library(SDL_Framework INTERFACE)

    target_include_directories(
        SDL_Framework INTERFACE
        ${THIRD_PARTY_DIR}/SDL/include
        ${THIRD_PARTY_DIR}/SDL2_image
        ${LIBRARY_DIR}/Frameworks/SDL2.framework/Headers
        ${LIBRARY_DIR}/Frameworks/SDL2_image.framework/Headers
    )

    target_link_options(
        SDL_Framework INTERFACE
        "-F${LIBRARY_DIR}/Frameworks"

    )

    target_link_libraries(
        SDL_Framework INTERFACE
        "-framework SDL2"
        "-framework SDL2_image"
    )

    target_link_libraries(
        MeowStandalone
        PUBLIC
        SDL_Framework
    )
endif ()