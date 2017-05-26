#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"
#include <unistd.h>
#include "pong.h"

int main (int argc, char *argv[]) {

    int error;
    int sock;

    //just test details
    char *str1 = "USER jim bob joe dean\r\n";
    char *str2 = "NICK bird928man\r\n";
    char *str3 = "JOIN #runescape\r\n";

    sock = net_connect ("irc.rizon.net", 6667, &error);

    net_send (sock, str1, strlen(str1));
    net_send (sock, str2, strlen(str2));

    char buf[1024+1];
    while (net_receive(sock, buf, 1024)) {
        printf ("%s\n", buf);
        if (!is_ping  (buf)) {
            make_pong (buf);
            printf ("->%s\n", buf);
            net_send  (sock, buf, strlen(buf));
        }
        memset (buf, '\0', 1024);
    }

    net_disconnect (sock);

    printf ("error code: %d\n", error);
    printf ("fd->%d\n", sock);
    return 0;

}
