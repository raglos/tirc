#include "pong.h"
#include <string.h>

//
// determines if str is a ping from the server
//
int is_ping (char *str) {
    char buf[7];
    strncpy(str, buf, 6);
    if (!strcmp(buf, "PING :")) {
        //it is a ping
        return 0;
    }
    return 1;
}

//
// changes the first 6 char's of *str
// from "PING :" to "PONG :"
//
void make_pong (char *str) {
    strncpy(str, "PONG :", 6);
}
