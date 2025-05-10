#ifndef STRENGTH_CHECK_H
#define STRENGTH_CHECK_H

#include <stdbool.h>

typedef struct {
    int total;
    int length_strength;
    int compromise_strength;
    int charset_strength;
    int uniqueness_strength;
    int repetition_strength;
} PasswordStrength;

PasswordStrength evaluate_password_strength(char* password);

#endif
