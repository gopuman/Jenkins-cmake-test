#include "../src/utils.h"
#include "../src/utils.cpp"
#include <gtest/gtest.h>

// Test case for the print_message function
TEST(UtilsTest, PrintMessage) {
    std::string message = "Test message";
    testing::internal::CaptureStdout();
    print_message(message);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Test message\n");
}