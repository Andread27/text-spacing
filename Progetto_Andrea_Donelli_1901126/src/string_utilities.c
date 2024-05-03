#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "string_utilities.h"


bool control(char c) {
    int b1 = (c >> 7) & 1 ? 1 : 0;
    int b2 = (c >> 6) & 1 ? 1 : 0;

    if (b1 == 1 && b2 == 0) {
        return true;
    }

    return false;
}


int lenString(char *word) {
    int l = 0;
    bool check = false;

    for (int i = 0; i < strlen(word); i++) {
        check = control(word[i]);
        if (!check) {
            l++;
        }
    }

    return l;
}


char *repeatSpace(int n) {
    char *copy = (char *)malloc(sizeof(char) * (n + 1));

    for (int i = 0; i < n; i++) {
        copy[i] = ' ';
    }

    copy[n] = '\0';

    return copy;
}


void resetString(char *stringa, int len) {
    for (int i = 0; i < len; i++) {
        stringa[i] = '\0';
    }
}

