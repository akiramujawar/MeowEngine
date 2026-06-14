message(STATUS "Configuring console build")

target_compile_definitions(MeowEngine PUBLIC __ENABLE_TRACY__)
#target_compile_definitions(MeowEngine PUBLIC __MULTI_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)

# Platform specific for apple (will come on this while working on web & windows) - painful stuff ehhhh
if(APPLE)
    target_link_libraries(
        MeowStandalone
        PRIVATE
        "-framework AppKit"
        "-framework Foundation"
        "-framework UniformTypeIdentifiers"
        "-framework Cocoa"
    )

    # give the RPath for linking our custom dependencies/Frameworks
    set_target_properties(
        MeowStandalone
        PROPERTIES
        BUILD_RPATH "@loader_path/engine/dependencies/Frameworks"
    )

endif()

message(STATUS "Running external command")

# Run external commands after building the MeowEngine
add_custom_command(
    TARGET MeowStandalone
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_PATH}
    COMMAND ENGINE_PATH=${CMAKE_SOURCE_DIR}
            ${INSTALLER_DIR}/./cmake-post-build.sh
            -p console
)