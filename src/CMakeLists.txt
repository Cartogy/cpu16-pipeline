add_library(src main.cpp)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(StateElements)
add_subdirectory(MicroArch)
add_subdirectory(Pipeline)

target_link_libraries(${PROJECT_NAME} PUBLIC StateElements)
