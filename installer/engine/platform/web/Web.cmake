message(STATUS "Configuring web build")

target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __WEB__)

#set_target_properties(
#    MeowEngine
#    PROPERTIES
#    LINK_FLAGS
#    "-O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"['png', 'jpg']\" -s USE_WEBGL2=1 --preload-file ../../../../engine/assets@/assets"
#)

message(STATUS "Linking sandbox & engine assets to wasm")

target_link_options(MeowStandalone PRIVATE
    "--preload-file=${CMAKE_SOURCE_DIR}/engine/assets@/engine/assets"
    "--preload-file=${PROJECT_PATH}/assets@/assets"
)

# When the build is complete we will run the 'cmake-post-build.sh' script.
add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_PATH}
    COMMAND ENGINE_PATH=${CMAKE_SOURCE_DIR}
            ${INSTALLER_DIR}/./cmake-post-build.sh
            -p web
)