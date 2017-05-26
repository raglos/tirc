#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net.h"
#include <unistd.h>
#include "pong.h"
#include "state.h"
#include <signal.h>

void sighandler (int);
volatile sig_atomic_t run = 0;
static int sock = 0;
static state_t state;

int main (int argc, char *argv[]) {

    signal (SIGINT, &sighandler);
    signal (SIGTSTP, &sighandler);

    int error;
    state_init (&state, "BirdMan928");

    //just test details
    char *str1 = "USER jim bob joe dean\r\n";
    char *str2 = "NICK bird928man\r\n";
    char *str3 = "JOIN #runescape\r\n";

    sock = net_connect ("chat.freenode.net", 6667, &error);

    net_send (sock, str1, strlen(str1));
    net_send (sock, str2, strlen(str2));

while (!run) {
    char *buf = calloc (1, 1024+1);
    int recv_len = 0;
    while ((recv_len = net_receive(sock, buf, 1024))) {
        printf ("%s\n", buf);
        if (!is_ping  (buf)) {
            make_pong (buf);
            printf    ("->%s\n", buf);
            net_send  (sock, buf, strlen(buf));
            state.connected = 1;
            continue;
        }

        if (state.connected && !state.joined)
            net_send (sock, str3, strlen (str3));

        // might replace with reg. char buf[] and
        // memset with '\0' instead if its "better"...
        free (buf);
        buf = calloc (1, 1024+1);
    }
}

    net_disconnect (sock);
    state_free (&state);

    printf ("error code: %d\n", error);
    printf ("fd->%d\n", sock);
    return 0;

}

void sighandler (int i) {
    run = 1;
    net_disconnect (sock);
    state_free (&state);
    puts ("\nGood bye, cruel world.");
    exit (1);
}
