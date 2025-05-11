#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../include/strength_check.h"
#include "../include/compromise_check.h"

// Sila aktualne vytvoreneho hesla
int evaluate_password_strength(char* password) {
    int strength = 0;
    int length = strlen(password);

    // 1. Delka hesla
    if (length >= 12) {
        strength++;
    }

    // 2. Neni kompromitovane
    if (!is_password_compromised(password)) {
        strength++;
    }

    // 3. Obsahuje vsechny typy znaku
    bool has_upper = false, has_lower = false, has_digit = false, has_symbol = false;
    for (int i = 0; i < length; ++i) {
        if (isupper(password[i])) has_upper = true;
        else if (islower(password[i])) has_lower = true;
        else if (isdigit(password[i])) has_digit = true;
        else has_symbol = true;
    }
    if (has_upper && has_lower && has_digit && has_symbol) {
        strength++;
    }

    // 4. 70% unikatnich znaku
    int unique_count = 0;
    bool seen[256] = { false };
    for (int i = 0; i < length; ++i) {
        unsigned char c = (unsigned char)password[i];
        if (!seen[c]) {
            seen[c] = true;
            unique_count++;
        }
    }
    if (length > 0 && ((float)unique_count / length) >= 0.7f) {
        strength++;
    }

    // 5. maximalne 2 stejne znaky za sebou
    bool has_repetition = false;
    for (int i = 2; i < length; ++i) {
        if (password[i] == password[i - 1] && password[i] == password[i - 2]) {
            has_repetition = true;
            break;
        }
    }
    if (!has_repetition) {
        strength++;
    }

    return strength;
}
