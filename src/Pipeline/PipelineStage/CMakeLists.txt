add_library(PipelineStage pipeline_stage.cpp)




target_include_directories(PipelineStage PUBLIC "${PROJECT_SOURCE_DIR}/src/")
target_include_directories(PipelineStage PUBLIC "${PROJECT_SOURCE_DIR}/src/Pipeline/")
