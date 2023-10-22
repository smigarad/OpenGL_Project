cmake_minimum_required(VERSION 3.15)

project(ZPG)

# Compiler options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -fsanitize=address")

# Transformation library
file(GLOB TRANSFORMATION_SOURCES "src/transformations/*.cpp")
add_library(transformationlib STATIC ${TRANSFORMATION_SOURCES})
target_include_directories(transformationlib PUBLIC "header/transformations")

# Shader library
file(GLOB SHADER_SOURCES "src/shaders/*.cpp")
add_library(shaderlib STATIC ${SHADER_SOURCES})
target_include_directories(shaderlib PUBLIC "header/shaders")

# Source files for the main executable
file(GLOB MAIN_SOURCES "src/*.cpp")

# Main executable
add_executable(main ${MAIN_SOURCES})

# Include directories for the main executable
target_include_directories(main PUBLIC "header" "models")


# Link the main executable with transformation and shader libraries and other required libraries
target_link_libraries(main transformationlib shaderlib glfw GL pthread GLEW)

# Set the output directory for the executable
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
