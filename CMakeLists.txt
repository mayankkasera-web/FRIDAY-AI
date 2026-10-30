# FRIDAY AI — Personal AI Assistant
# Root CMake configuration

cmake_minimum_required(VERSION 3.25)

project(friday_ai
    VERSION 0.1.0
    DESCRIPTION "FRIDAY AI — Personal AI Assistant"
    LANGUAGES CXX
)

# Require C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the executable target with all source files
add_executable(friday
    src/main.cpp
    src/commands.cpp
    src/notes.cpp
    src/config.cpp
)

# Tell the compiler where to find our header files
target_include_directories(friday PRIVATE include)

# Enable compiler warnings
target_compile_options(friday PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)