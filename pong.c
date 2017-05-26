#include "pong.h"
#include <string.h>
#include <stdio.h>
//
// determines if str is a ping from the server
//
int is_ping (char *str) {
    const char *vs = "PING :";
    int i = 0;
    for (i; i < 6; i++) {
//        printf ("%c - %c\n", vs[i], str[i]);
        if (vs[i] != str[i]) return 1;
    }
    return 0;
}

//
// changes the first 6 char's of *str
// from "PING :" to "PONG :"
//
void make_pong (char *str) {
    strncpy(str, "PONG :", 6);
}
