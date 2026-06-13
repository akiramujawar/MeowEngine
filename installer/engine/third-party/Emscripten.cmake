
if(EMSCRIPTEN)
    target_include_directories(MeowEngine PRIVATE
        ${LIBRARY_DIR}/emscripten-6-0-0/upstream/emscripten/system/include
    )
endif()