add_library(MicroArch microarch.cpp)

target_include_directories(MicroArch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Adds path of src
target_include_directories(MicroArch PUBLIC "${PROJECT_SOURCE_DIR}/src/")
