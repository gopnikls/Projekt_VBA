#include "../unity/unity.h"
#include "test_password_generator.h"
#include "test_strength_check.h"
#include "test_compromise_check.h"

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // Password generator tests
    RUN_TEST(test_generate_password_returns_non_null);
    RUN_TEST(test_generate_password_length);

    // Strength check tests
    RUN_TEST(test_weak_password);
    RUN_TEST(test_strong_password);


    RUN_TEST(test_compromised_password);
    RUN_TEST(test_non_compromised_password);

    return UNITY_END();
}