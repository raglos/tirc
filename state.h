#ifndef STATE_H
#define STATE_H

struct state;
typedef struct state {
    char connected;
    char joined;
    char *nick;
     
} state_t;

void state_init (state_t *, char *);
void state_free (state_t *);

#endif
