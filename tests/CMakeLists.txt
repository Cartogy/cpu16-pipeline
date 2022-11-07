
add_executable(state_elements_test state_elements_test.cc)

target_link_libraries(state_elements_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(state_elements_test)
