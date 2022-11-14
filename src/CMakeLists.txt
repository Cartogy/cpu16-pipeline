add_library(src main.cpp)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(StateElements)
add_subdirectory(MicroArch)
add_subdirectory(Pipeline)
add_subdirectory(InstructionMemory)
add_subdirectory(Memory)
add_subdirectory(ControlUnit)

target_link_libraries(${PROJECT_NAME} PUBLIC StateElements)
