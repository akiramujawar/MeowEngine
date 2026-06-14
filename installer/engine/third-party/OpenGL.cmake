
if(EMSCRIPTEN)
    target_link_options(MeowStandalone PUBLIC
        "-sUSE_WEBGL2=1"
    )
elseif (APPLE)
    find_package(OpenGL REQUIRED)

    add_library(OpenGL_Framework INTERFACE)

    target_link_options(OpenGL_Framework INTERFACE
        "-F${LIBRARY_DIR}/Frameworks"
    )

    target_link_libraries(OpenGL_Framework INTERFACE
        "-framework OpenGL"
    )

    target_link_libraries(
        MeowStandalone
        PUBLIC
        ${OPENGL_LIBRARIES} OpenGL_Framework
    )
endif ()