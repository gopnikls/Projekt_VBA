#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/compromise_check.h"

bool is_password_compromised(char* password) {
    FILE* file = fopen("../data/100k-most-used-passwords-NCSC.txt", "r");
    if (file == NULL) {
        perror("Error opening password list file");
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strcmp(line, password) == 0) {
            fclose(file);
            return true; // Heslo bylo nalezeno v seznamu
        }
    }

    fclose(file);
    return false; // Heslo nenalezeno
}
