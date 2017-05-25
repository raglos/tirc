#include <stdio.h>
#include <stdlib.h>
#include "net.h"

int main (int argc, char *argv[]) {


    int error;
    net_connect ("irc.rizon.net", 6667, &error);

    printf ("error code: %d\n", error);
    return 0;

}
