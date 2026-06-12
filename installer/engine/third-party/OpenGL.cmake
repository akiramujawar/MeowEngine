find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED) #required by tracy

add_library(OpenGL_Framework INTERFACE)

target_link_options(OpenGL_Framework INTERFACE
    "-F${LIBRARY_DIR}/Frameworks"
)

target_link_libraries(OpenGL_Framework INTERFACE
    "-framework OpenGL"
)

target_link_libraries(
    MeowEngine
    PUBLIC
    ${OPENGL_LIBRARIES} OpenGL_Framework
)