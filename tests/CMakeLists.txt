
add_executable(state_elements_test state_elements_test.cc)
add_executable(pipeline_registers_test pipeline_registers.cc)
add_executable(instruction_memory_test instruction_memory.cc)
add_executable(pipeline_stage_test pipeline_stage_test.cc)
add_executable(memory_test memory_test.cc)

target_link_libraries(state_elements_test GTest::gtest_main StateElements)
target_link_libraries(pipeline_registers_test GTest::gtest_main PipelineRegister)
target_link_libraries(instruction_memory_test GTest::gtest_main InstructionMemory)
target_link_libraries(pipeline_stage_test GTest::gtest_main InstructionMemory PipelineStage PipelineRegister StateElements)
target_link_libraries(memory_test GTest::gtest_main)


target_include_directories(state_elements_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")

target_include_directories(pipeline_registers_test PUBLIC "${PROJECT_SOURCE_DIR}/src/Pipeline/")

target_include_directories(instruction_memory_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")

target_include_directories(pipeline_stage_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")

target_include_directories(memory_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")



include(GoogleTest)
gtest_discover_tests(state_elements_test)
gtest_discover_tests(pipeline_registers_test)
gtest_discover_tests(instruction_memory_test)
gtest_discover_tests(pipeline_stage_test)
gtest_discover_tests(memory_test)
