#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"
#include <unistd.h>

const char *m_pong = "PONG :";

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
    
    int ponged = 0;    

    char buf[1024+1];
    while (net_receive(sock, buf, 1024)) {
        if (ponged == 1) {
            net_send (sock, str3, strlen(str3));
            ponged = 2;    
        }

        printf ("%s\n", buf);
        //PING: 12345678 -> PONG: 12345678
        if (buf[0] == 'P' && strlen(buf) < 30) {
            (void) memmove(buf, m_pong, strlen(m_pong));
            net_send (sock, buf, strlen(buf)); 
            ponged++;
        }
        memset (buf, '\0', 1024);
    }

    net_disconnect (sock);

    printf ("error code: %d\n", error);
    printf ("fd->%d\n", sock);
    return 0;

}
