add_library(Emulator emulator.cpp)

target_include_directories(Emulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Emulator PUBLIC "${PROJECT_SOURCE_DIR}/src/")
