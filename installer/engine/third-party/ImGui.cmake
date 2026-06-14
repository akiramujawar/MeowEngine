#include_directories(${THIRD_PARTY_DIR}/imgui)
#include_directories(${THIRD_PARTY_DIR}/imgui/backends)

add_library(
    ImGui STATIC

    ${THIRD_PARTY_DIR}/imgui/imgui.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_draw.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_tables.cpp
    ${THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp

    # Optional
    ${THIRD_PARTY_DIR}/imgui/imgui_demo.cpp

    # Backends
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl2.cpp
    ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(
    ImGui
    PUBLIC
    ${THIRD_PARTY_DIR}/imgui
    ${THIRD_PARTY_DIR}/imgui/backends
)


if(EMSCRIPTEN)
    target_compile_options(ImGui PRIVATE
        "-sUSE_SDL=2"
    )

    target_link_options(ImGui PRIVATE
        "-sUSE_SDL=2"
    )
elseif (APPLE)
    target_link_libraries(
        ImGui
        PUBLIC
        SDL_Framework
        ${OPENGL_LIBRARIES}
    )
endif ()

target_link_libraries(
    MeowEngine
    PUBLIC
    ImGui
)