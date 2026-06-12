message(STATUS "Configuring console build")

target_compile_definitions(MeowEngine PUBLIC __ENABLE_TRACY__)
#target_compile_definitions(MeowEngine PUBLIC __MULTI_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)