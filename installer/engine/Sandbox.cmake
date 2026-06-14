


set(SANDBOX_DIRECTORY ${PROJECT_PATH}/source)

# Recursive include directories
set(ALL_INCLUDE_DIRS)

file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS
    ${SANDBOX_DIRECTORY}/*.cpp
)

foreach(ROOT_DIR ${SANDBOX_DIRECTORY})
    list(APPEND ALL_INCLUDE_DIRS ${ROOT_DIR})

    file(GLOB_RECURSE ROOT_ENTRIES CONFIGURE_DEPENDS
        "${ROOT_DIR}/*"
    )

    foreach(ENTRY ${ROOT_ENTRIES})
        get_filename_component(DIR "${ENTRY}" DIRECTORY)

        if(IS_DIRECTORY "${DIR}")
            list(APPEND ALL_INCLUDE_DIRS "${DIR}")
        endif()
    endforeach()
endforeach()

list(REMOVE_DUPLICATES ALL_INCLUDE_DIRS)

add_library(
    Sandbox STATIC

    ${SANDBOX_SOURCES}
)

target_link_libraries(
    Sandbox
    PUBLIC
    MeowEngine
)