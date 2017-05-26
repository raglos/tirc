#include "state.h"
#include <string.h>
#include <stdlib.h>

//
// inits a state struct
// assumes malloc doesnt fail and state is !0 :D
//
void state_init (state_t *state, char *nick) {
    
    size_t len = strlen (nick);

    state->connected = 0;
    state->joined    = 0;
    state->nick      = malloc (len+1);
    strncpy(state->nick, nick, len);
    state->nick[len] = '\0'; //to be sure...
    
}

void state_free (state_t *state) {
    if (state) free (state->nick);
}
