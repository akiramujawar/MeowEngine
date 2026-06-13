message(STATUS "Configuring web build")

target_compile_definitions(MeowEngine PUBLIC __SINGLE_THREAD__)
target_compile_definitions(MeowEngine PUBLIC __WEB__)
#message(STATUS sd="ds")