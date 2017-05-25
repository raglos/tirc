#include <stdio.h>
#include <stdlib.h>
#include "net.h"

int main (int argc, char *argv[]) {

    int error;
    int sock;
    
    sock = net_connect ("irc.rizon.net", 6667, &error);
    net_disconnect (sock);

    printf ("error code: %d\n", error);
    printf ("fd->%d\n", sock);
    return 0;

}
