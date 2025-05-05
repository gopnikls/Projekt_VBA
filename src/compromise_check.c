#include <stdio.h>
#include <stdlib.h>
#include "compromise_check.h"

bool is_password_compromised(char* password){
	FILE* file = fopen ("data/100k-most-used-passwords-NCSC.txt", "r");
	if(file == NULL){
		puts("Error during reading file.");
		return NULL;
	}

	bool is_compromised = true;
	//TODO Implementovat porovnani vygenerovaneho hesla s hesly v souboru 100k-most-used-passwords-NCSC.txt

	return is_compromised;
}
