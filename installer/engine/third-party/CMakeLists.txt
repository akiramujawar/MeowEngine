
if(EMSCRIPTEN)
    include(Emscripten.cmake)
endif ()

include(OpenGL.cmake)

if(NOT EMSCRIPTEN)
    include(OpenCL.cmake)
endif ()

include(SDL.cmake)
include(GLM.cmake)
include(TinyObjectLoader.cmake)
include(MagicEnum.cmake)
include(ConcurrentQueue.cmake)
include(Entt.cmake)
include(PhysX.cmake)
include(ImGui.cmake)
include (YamlCpp.cmake)

if(NOT EMSCRIPTEN)
    include(Tracy.cmake)
endif ()

if(NOT EMSCRIPTEN)
    include(NativeFileDialog.cmake)
endif ()