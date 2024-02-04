cmake_minimum_required(VERSION 3.15)

project(ZPG)

# Compiler options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -fsanitize=address")

# Find pkg-config
include_directories(/usr/include)

# Transformation library
file(GLOB TRANSFORMATION_SOURCES "src/transformations/*.cpp")
add_library(transformationlib STATIC ${TRANSFORMATION_SOURCES})
target_include_directories(transformationlib PUBLIC "header/transformations")

# Shader library
file(GLOB SHADER_SOURCES "src/shaders/*.cpp")
add_library(shaderlib STATIC ${SHADER_SOURCES})
target_include_directories(shaderlib PUBLIC "header/shaders")

# Light library
file(GLOB LIGHT_SOURCES "src/lights/*.cpp")
add_library(lightlib STATIC ${LIGHT_SOURCES})
target_include_directories(lightlib PUBLIC "header/lights")

# Source files for the main executable
file(GLOB MAIN_SOURCES "src/*.cpp")

# Main executable
add_executable(main ${MAIN_SOURCES})

# Include directories for the main executable
target_include_directories(main PUBLIC "header" "models_h" ${STB_INCLUDE_DIRS} )

#find_package(imgui CONFIG REQUIRED)
# Link the main executable with transformation and shader libraries and other required libraries
target_link_libraries(main transformationlib lightlib shaderlib ${STB_INCLUDE_DIRS} glfw GL pthread GLEW GLU  assimp)

# Set the output directory for the executable
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

