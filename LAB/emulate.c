#include "emulate.h"

typedef struct StateTAG {
    int *mem;
    size_t limit;

    int regs[256];
}*StateHANDLE;

State state_init(size_t memsize)
{
    int i;
    StateHANDLE ret = malloc(sizeof(struct StateTAG));
    ret->mem = malloc(sizeof(int)*memsize);
    ret->limit = memsize;
    
    for (i=0; i<256; ++i) regs[i] = 0;
    
    return ret;
}

State state_load(State s, int *data, size_t size)
{
    int i;
    StateHANDLE this = s;
    if (!this) goto state_load_ret;

    for (i=0; i<size; ++i) this->mem[i] = data[i];

state_load_ret:
    return this;
}
    


void state_close(State s)
{
    StateHANDLE this = s;
    if (this) {
        if (this->limit > 0 && this->mem)
            free(this->mem);
        free(this);
    }
}


