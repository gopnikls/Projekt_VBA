#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Konstanty pro znaky
const char* UPPERCASE_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* LOWERCASE_CHARS = "abcdefghijklmnopqrstuvwxyz";
const char* DIGIT_CHARS = "0123456789";
const char* SPECIAL_CHARS = "`~!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?";

// Funkce generovani hesla
char* generate_password(int password_length, bool use_uppercase, bool use_lowercase,
    bool use_digits, bool use_symbols) {

    if (password_length <= 0) {
        return NULL;
    }

    // Alokace pameti
    char* password = malloc(password_length + 1);
    if (password == NULL) {
        return NULL;
    }

    // Sestaveni poolu znaku
    char pool[256] = "";
    if (use_uppercase) strncat(pool, UPPERCASE_CHARS, sizeof(pool) - strlen(pool) - 1);
    if (use_lowercase) strncat(pool, LOWERCASE_CHARS, sizeof(pool) - strlen(pool) - 1);
    if (use_digits) strncat(pool, DIGIT_CHARS, sizeof(pool) - strlen(pool) - 1);
    if (use_symbols) strncat(pool, SPECIAL_CHARS, sizeof(pool) - strlen(pool) - 1);

    int pool_length = strlen(pool);
    if (pool_length == 0) {
        free(password);
        return NULL;
    }

    // Generovani hesla z poolu
    for (int i = 0; i < password_length; ++i) {
        int idx = rand() % pool_length;
        password[i] = pool[idx];
    }
    password[password_length] = '\0';

    return password;
}
