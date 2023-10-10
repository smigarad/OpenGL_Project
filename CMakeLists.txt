cmake_minimum_required(VERSION 3.0)

project(MyProject)

# Compiler options
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -fsanitize=address")

# Source files
file(GLOB SOURCES "src/*.cpp")

# Header files
include_directories("header" "models")

# Create a library from source files
add_library(mylibrary STATIC ${SOURCES})

# Main executable
add_executable(main src/main.cpp)

# Link the executable with the library and required libraries
target_link_libraries(main mylibrary glfw GL pthread GLEW)

# Set the output directory for the executable
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})