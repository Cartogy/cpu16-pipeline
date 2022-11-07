
add_executable(state_elements_test state_elements_test.cc)

target_link_libraries(state_elements_test GTest::gtest_main StateElements)

target_include_directories(state_elements_test PUBLIC "${PROJECT_SOURCE_DIR}/src/")

include(GoogleTest)
gtest_discover_tests(state_elements_test)
