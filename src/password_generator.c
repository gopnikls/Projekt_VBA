#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "password_generator.h"
#include "compromise_check.h"
#include "strength_check.h"

// Konstanty pro znaky
const char* UPPERCASE_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* LOWERCASE_CHARS = "abcdefghijklmnopqrstuvwxyz";
const char* DIGIT_CHARS = "0123456789";
const char* SPECIAL_CHARS = "`~!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?";

// Prototypy funkcÌ
char* generate_password(int password_length, bool use_uppercase, bool use_lowercase,
	bool use_digits, bool use_symbols);
PasswordStrength evaluate_password_strength(char* password);

// Funkce pro generov·nÌ silnÈho hesla podle kritÈriÌ
char* generate_strong_password(int password_length, bool use_uppercase, bool use_lowercase,
	bool use_digits, bool use_symbols) {
	char* password;
	PasswordStrength strength;

	do {
		// Generuj heslo
		password = generate_password(password_length, use_uppercase, use_lowercase, use_digits, use_symbols);
		// Zhodnoù sÌlu hesla
		strength = evaluate_password_strength(password);

		// Pokud heslo nevyhovuje podmÌnk·m, generuj novÈ heslo
	} while (!(strength.length_strength && strength.compromise_strength && strength.charset_strength &&
		strength.uniqueness_strength && strength.repetition_strength));

	return password;
}

// Funkce pro generov·nÌ hesla
char* generate_password(int password_length, bool use_uppercase, bool use_lowercase,
	bool use_digits, bool use_symbols) {
	if (password_length <= 0)
		return "Please, enter valid length";

	char* password = malloc(password_length + 1);
	if (password == NULL)
		return "Memory allocation error";

	// SestavenÌ poolu znak˘
	char pool[256] = "";
	if (use_uppercase) strncat(pool, UPPERCASE_CHARS, sizeof(pool) - strlen(pool) - 1);
	if (use_lowercase) strncat(pool, LOWERCASE_CHARS, sizeof(pool) - strlen(pool) - 1);
	if (use_digits) strncat(pool, DIGIT_CHARS, sizeof(pool) - strlen(pool) - 1);
	if (use_symbols) strncat(pool, SPECIAL_CHARS, sizeof(pool) - strlen(pool) - 1);

	int pool_length = strlen(pool);
	if (pool_length == 0) {
		free(password);
		return "Please, enter valid parameters (at least one must be ON).";
	}

	// Generov·nÌ hesla
	for (int i = 0; i < password_length; ++i) {
		int idx = rand() % pool_length;
		password[i] = pool[idx];
	}
	password[password_length] = '\0';

	return password;
}
