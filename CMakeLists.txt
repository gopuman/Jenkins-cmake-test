include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyCppProject VERSION 1.0 LANGUAGES CXX)

# Add a library target
add_library(utils src/utils.cpp)

# Add an executable target
add_executable(hello_world src/main.cpp)

# Include the include/ directory for header files
target_include_directories(utils PUBLIC include)
target_include_directories(hello_world PRIVATE include)

# Link the library to the executable
target_link_libraries(hello_world PRIVATE utils)

# Add compiler flags
target_compile_options(hello_world PRIVATE -Wall -Wextra -Werror)

# Enable testing for the project
enable_testing()

# Add the tests directory
add_subdirectory(tests)