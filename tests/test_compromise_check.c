#include "../unity/unity.h"
#include "../include/compromise_check.h"

void test_compromised_password() {
    // Assuming "password123" is in the compromised passwords list
    TEST_ASSERT_TRUE(is_password_compromised("password123"));
}

void test_non_compromised_password() {
    // Assuming "securePassword2025" is not in the compromised passwords list
    TEST_ASSERT_FALSE(is_password_compromised("securePassword2025"));
}


