
add_library(
    YamlCPP STATIC

    ${THIRD_PARTY_DIR}/yamlcpp/src/binary.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/convert.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/depthguard.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/directives.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/emit.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/emitfromevents.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/emitter.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/emitterstate.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/emitterutils.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/exceptions.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/exp.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/memory.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/node.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/node_data.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/nodebuilder.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/nodeevents.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/null.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/ostream_wrapper.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/parse.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/parser.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/regex_yaml.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/scanner.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/scanscalar.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/scantag.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/scantoken.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/simplekey.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/singledocparser.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/stream.cpp
    ${THIRD_PARTY_DIR}/yamlcpp/src/tag.cpp
)

#add_library(YamlCPP INTERFACE)

target_include_directories(
    YamlCPP
    PUBLIC
    ${THIRD_PARTY_DIR}/yamlcpp/include
)

target_link_libraries(
    MeowEngine
    PUBLIC
    YamlCPP
)