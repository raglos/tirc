#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>

#include "net.h"

#define net_die(x, y) {              \
        fprintf (stderr, "%s\n", x); \
        *error_out = y;              \
        return -1;                   \
}

//
// returns a fd for the socket
// if an error occured, its value will be assigned to int *error_out param.
//
int net_connect(const char *_host, const int port, int *error_out) {
    int err, sock;
    
    struct sockaddr_in           serv;
    struct hostent       *host = NULL;
    struct in_addr **addr_list = NULL;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) net_die("Error could not create socket.", NETESOCKET );

    host = gethostbyname ( _host );
    if (!host)    net_die("Error gethostbyname().", NETEHOST );

    addr_list = (struct in_addr **) host->h_addr_list;
    serv.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[0]));
    serv.sin_family      = AF_INET;
    serv.sin_port        = htons( port );

    err = connect(sock, (struct sockaddr *)&serv, sizeof serv);
    if (err < 0)  net_die("Error, connection failed.", NETECON );

    return sock;
}
