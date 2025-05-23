/*
 ============================================================================
 Name        : password_generator.c
 Author      : Yanko Yan, Fiala Adam, Fiala Jiří
 Version     :
 Copyright   : 2025 (c) VUT v Brně
 Description : Secure password generator, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/compromise_check.h"
#include "../include/password_generator.h"
#include "../include/strength_check.h"

//Prototypy funkci
bool get_answer(char* question);
int read_int();
void show_menu();
void show_password_and_its_parameters(char* password, int password_length, bool use_uppercase,
									  bool use_lowercase, bool use_digits, bool use_symbols, int strenght);

int main(void) {
	srand(time(NULL));

	int password_length = 12;
	bool use_uppercase = true;
	bool use_lowercase = true;
	bool use_digits = true;
	bool use_symbols = true;
	char* password = strdup("");

	while (1){
		//Zobrazeni hesla, jeho sily, parametru se kterymi bylo vygenerovano a menu
		int strength = evaluate_password_strength(password);
		show_password_and_its_parameters(password, password_length, use_uppercase, use_lowercase, use_digits, use_symbols, strength);
		show_menu();

		//Nacteni zvolene polozky menu
		int choice = read_int();

		switch (choice){
		case 1: {
			// Generace hesla
			int max_strength = calculate_password_strength(password_length, use_uppercase, use_lowercase, use_digits, use_symbols); //Vypocet maximalni sily hesla
			int pokusy = 0;  // Pocet pokusu

			do {
				// Generovani hesla
				password = generate_password(password_length, use_uppercase, use_lowercase, use_digits, use_symbols);
				strength = evaluate_password_strength(password);
				pokusy++;

				// Pokud heslo po 80 pokusech nema nejvyssi moznou silu, snizime ji
				if (pokusy > 80) {
					max_strength--;
					break;
				}

			} while (strength < max_strength);  // Generuji se hesla dokud nesplni minimalni silu
			break;
		}
		case 2: {
			//Nacteni delky hesla
			do {
				puts("Enter password length (minimum 8): ");
				password_length = read_int();

				if (password_length < 8) {
					puts("Password too short! Minimum is 8 characters.");
				}
			} while (password_length < 8);

			//Nacteni parametru pro generaci hesla
			use_uppercase = get_answer("Do you want to include uppercase?");
			use_lowercase = get_answer("Do you want to include lowercase?");
			use_digits = get_answer("Do you want to include digits?");
			use_symbols = get_answer("Do you want to include special symbols?");
			break;
		}
		case 3: {
			free(password);
			exit(0);
			break;
		}
		}
	}
	free(password);
	return EXIT_SUCCESS;
}

// Vypocet maximalni mozne sily hesla
int calculate_password_strength(int password_length, bool use_uppercase, bool use_lowercase,
	bool use_digits, bool use_symbols) {
	int strength = 5;

	// Pokud je delka min nez 12
	if (password_length < 12) {
		strength--;
	}

	// Pokud nejsou zapnuty vsechny parametry
	if (!use_uppercase || !use_lowercase || !use_digits || !use_symbols) {
		strength--;
	}

	return strength;
}

//Funkce pro bezpecne cteni celych cisel
int read_int() {
    char buffer[100];
    int value;
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%d", &value) == 1) return value;
        printf("Invalid input! Try again.\n");
    }
}

//Funkce pro konverze na mala pismena
void to_lower(char* str){
	for (int i = 0; str[i]; ++i)
		str[i] = tolower((unsigned char)str[i]);
}

//Funkce pro zpracovani odpovedi uzivatele pri zadani parametru generace
bool get_answer(char* question){
	char input[10];
	while(1){
		printf("%s (y/n): ", question);

		if(fgets(input, sizeof(input), stdin) == NULL) continue;

		input[strcspn(input, "\n")] = '\0';
		to_lower(input);

		if (strcmp(input, "y") == 0 || strcmp(input, "yes") == 0) return true;
		else if(strcmp(input, "n") == 0 || strcmp(input, "no") == 0) return false;
		else {
			puts("Invalid input! Try again.\n");
			continue;
		}
	}
}

void show_menu(){
	puts("\nMenu: ");
	puts("1.Generate password");
	puts("2.Change generator parameters");
	puts("3.Exit");
}

void show_password_and_its_parameters(char* password, int password_length, bool use_uppercase,
	bool use_lowercase, bool use_digits, bool use_symbols,
	int strength) {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	printf("Password: %s\n", password);
	printf("Strength: %d/5\n", strength);


	printf("\nParameters: Length: %d | Uppercase: %s | Lowercase: %s | Digits: %s | Symbols: %s\n",
		password_length,
		use_uppercase ? "ON" : "OFF",
		use_lowercase ? "ON" : "OFF",
		use_digits ? "ON" : "OFF",
		use_symbols ? "ON" : "OFF");
}
