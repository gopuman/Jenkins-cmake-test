# Add the test executable
add_executable(tests test_main.cpp)

# Link GoogleTest and utils to the test executable
target_link_libraries(tests PRIVATE gtest gtest_main utils)

# Add compiler flags for tests
target_compile_options(tests PRIVATE -Wall -Wextra -Werror)

# Enable CTest (optional)
enable_testing()
add_test(NAME UtilsTests COMMAND tests)