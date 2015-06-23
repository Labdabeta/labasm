#ifndef EMULATE_H
#define EMULATE_H

typedef void *State;

State state_init(size_t);
void state_close(State);

State state_load(State,int*,size_t);
bool state_step(State);

#endif
