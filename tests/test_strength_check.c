#include "../unity/unity.h"
#include "../include/strength_check.h"

void test_weak_password() {
    int strength = evaluate_password_strength("1234");
    TEST_ASSERT_LESS_THAN_INT(3, strength);  // Expect strength to be less than 3
}

void test_strong_password() {
    int strength = evaluate_password_strength("&*3oaFfx.zNRK!");
    TEST_ASSERT_EQUAL_INT(5, strength);  // Expect strength to be 5
}
