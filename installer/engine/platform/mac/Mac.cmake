message(STATUS "Configuring Mac build")

target_compile_definitions(MeowEngine PUBLIC __ENABLE_TRACY__)
#target_compile_definitions(MeowEngine PUBLIC __MULTI_THREAD__)