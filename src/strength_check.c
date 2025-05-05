#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strength_check.h"
#include "compromise_check.h"

int evaluate_password_strength(char* password){
	int password_length = strlen(password);
	int strength = 0;

	//1 bod za dostatecnou delku hesla
	if(password_length >= 12)
		strength += 1;

	//1 bod za nenalezeni hesla v databazi
	if(!is_password_compromised(password))
		strength += 1;

	//TODO Overit, ze vsechny 4 mozne parametry(Uppercase, Lowercase, Digits, Symbols) jsou pouzity v hesle

	//TODO Overit pocet ruznych symbolu (minimalne 70% symbolu musi byt unikatni)

	//TODO Overit heslo na sekvence stejnych symbolu jako aaa, 111 (maximalne 2 za sebou)



	return strength;
}
