add_library(PipelineRegister pipeline_register.cpp)

target_include_directories(PipelineRegister INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(PipelineRegister PUBLIC "${PROJECT_SOURCE_DIR}/src/")
