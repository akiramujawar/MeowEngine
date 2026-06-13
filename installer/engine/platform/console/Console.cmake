message(STATUS "Configuring console build")

target_compile_definitions(MeowEngine PUBLIC __ENABLE_TRACY__)
#target_compile_definitions(MeowEngine PUBLIC __MULTI_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)

# Platform specific for apple (will come on this while working on web & windows) - painful stuff ehhhh
if(APPLE)
    target_link_libraries(
        MeowEngine
        PRIVATE
        "-framework AppKit"
        "-framework Foundation"
        "-framework UniformTypeIdentifiers"
        "-framework Cocoa"
    )

    # give the RPath for linking our custom dependencies/Frameworks
    set_target_properties(
        MeowEngine
        PROPERTIES
        BUILD_RPATH "@loader_path/dependencies/Frameworks"
    )

endif()

# Run external commands after building the MeowEngine
add_custom_command(
    TARGET MeowEngine
    POST_BUILD
    WORKING_DIRECTORY ${INSTALLER_DIR}
    COMMAND ./cmake-post-build.sh -p console
)