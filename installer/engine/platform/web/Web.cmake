message(STATUS "Configuring web build")

# -----
target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __WEB__)

#  ----- Link assets
message(STATUS "Linking sandbox & engine assets to wasm")

target_link_options(MeowStandalone PRIVATE
    "--preload-file=${CMAKE_SOURCE_DIR}/engine/assets@/engine/assets"
    "--preload-file=${CMAKE_SOURCE_DIR}/engine/shaders/compiled@/engine/shaders"

    "--preload-file=${PROJECT_PATH}/assets@/assets"
    "--preload-file=${PROJECT_PATH}/shaders/compiled@/shaders"

    "--preload-file=${PROJECT_PATH}/Editor.yml@/Editor.yml"
    "--preload-file=${PROJECT_PATH}/Sandbox.yml@/Sandbox.yml"
)

target_link_options(MeowStandalone PRIVATE
    -sALLOW_MEMORY_GROWTH=1
)

#---- DEBUG BUILD start

#target_compile_options(MeowStandalone PRIVATE
#    -O0
#    -g3
#    -fexceptions
#)

#target_link_options(MeowStandalone PRIVATE
#    -O0
#    -g3
#    -sASSERTIONS=2
#    -sSAFE_HEAP=1
#    -sSTACK_OVERFLOW_CHECK=2
#    -sEXCEPTION_STACK_TRACES=1
#    -fexceptions
#    -sALLOW_MEMORY_GROWTH=1
#)

#---- DEBUG BUILD end

# ----- When the build is complete we will run the 'cmake-post-build.sh' script.
add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_PATH}
    COMMAND ENGINE_PATH=${CMAKE_SOURCE_DIR}
            ${INSTALLER_DIR}/./cmake-post-build.sh
            -p web
)