#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "input_converte.h"

int converte(char *c) {
    char* p;
    long conv = strtol(c, &p, 10);
    if (errno != 0 || *p != '\0') {
        perror("ERRORE!");
        exit(1);
    }
    else {
        return (int) conv;
    }
}

