message(STATUS "Configuring web build")

# -----
target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __WEB__)

#  ----- Link assets
message(STATUS "Linking sandbox & engine assets to wasm")

target_link_options(MeowStandalone PRIVATE
    "--preload-file=${CMAKE_SOURCE_DIR}/engine/assets@/engine/assets"
    "--preload-file=${PROJECT_PATH}/assets@/assets"
)

# ----- When the build is complete we will run the 'cmake-post-build.sh' script.
add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_PATH}
    COMMAND ENGINE_PATH=${CMAKE_SOURCE_DIR}
            ${INSTALLER_DIR}/./cmake-post-build.sh
            -p web
)