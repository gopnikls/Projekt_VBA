#include "../unity/unity.h"
#include "../include/password_generator.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void test_generate_password_returns_non_null() {
    char* pwd = generate_password(12, true, true, true, true);
    TEST_ASSERT_NOT_NULL(pwd);
    free(pwd);
}

void test_generate_password_length() {
    int len = 16;
    char* pwd = generate_password(len, true, true, true, true);
    TEST_ASSERT_EQUAL_INT(len, strlen(pwd));
    free(pwd);
}
