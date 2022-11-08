
add_executable(state_elements_test state_elements_test.cc)
add_executable(pipeline_registers_test pipeline_registers.cc)

target_link_libraries(state_elements_test GTest::gtest_main StateElements)
target_link_libraries(pipeline_registers_test GTest::gtest_main PipelineRegister)


target_include_directories(state_elements_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")

target_include_directories(pipeline_registers_test PUBLIC "${PROJECT_SOURCE_DIR}/src/Pipeline/")

include(GoogleTest)
gtest_discover_tests(state_elements_test)
