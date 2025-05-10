#include <stdio.h>
#include <stdlib.h>
#include "compromise_check.h"

bool is_password_compromised(char* password) {
    FILE* file = fopen("data/100k-most-used-passwords-NCSC.txt", "r");
    if (file == NULL) {
        perror("Error opening password list file");
        return false; // Rad�ji pova�ujeme za nekompromitovan� p�i chyb�
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Odstran�me p��padn� \n na konci ��dku
        line[strcspn(line, "\r\n")] = '\0';
        if (strcmp(line, password) == 0) {
            fclose(file);
            return true; // Heslo bylo nalezeno v seznamu kompromitovan�ch
        }
    }

    fclose(file);
    return false; // Heslo nenalezeno
}
