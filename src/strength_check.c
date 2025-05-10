#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strength_check.h"
#include "compromise_check.h"

PasswordStrength evaluate_password_strength(char* password) {
    PasswordStrength strength = { 0 };

    int length = strlen(password);

    // 1. D�lka hesla
    if (length >= 12) {
        strength.length_strength = 1;
    }

    // 2. Nen� kompromitovan�
    if (!is_password_compromised(password)) {
        strength.compromise_strength = 1;
    }

    // 3. Obsahuje v�echny typy znak�
    bool has_upper = false, has_lower = false, has_digit = false, has_symbol = false;
    for (int i = 0; i < length; ++i) {
        if (isupper(password[i])) has_upper = true;
        else if (islower(password[i])) has_lower = true;
        else if (isdigit(password[i])) has_digit = true;
        else has_symbol = true;
    }
    if (has_upper && has_lower && has_digit && has_symbol) {
        strength.charset_strength = 1;
    }

    // 4. Unik�tn� znaky (alespo� 70 % znak� mus� b�t unik�tn�ch)
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
        strength.uniqueness_strength = 1;
    }

    // 5. Maxim�ln� 2 stejn� znaky za sebou
    bool has_repetition = false;
    for (int i = 2; i < length; ++i) {
        if (password[i] == password[i - 1] && password[i] == password[i - 2]) {
            has_repetition = true;
            break;
        }
    }
    if (!has_repetition) {
        strength.repetition_strength = 1;
    }

    // V�po�et celkov� s�ly
    strength.total =
        strength.length_strength +
        strength.compromise_strength +
        strength.charset_strength +
        strength.uniqueness_strength +
        strength.repetition_strength;

    return strength;
}
