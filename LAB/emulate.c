#include "emulate.h"

typedef struct StateTAG {
    int *mem;
    size_t limit;
    int time;

    int regs[256];
}*StateHANDLE;

State state_init(size_t memsize)
{
    int i;
    StateHANDLE ret = malloc(sizeof(struct StateTAG));
    ret->mem = malloc(sizeof(int)*memsize);
    ret->limit = memsize;
    ret->time = 0;
    
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


static int add(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a + *b;
    return 0;
}

static int sub(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a + *b;
    return 0;
}

static int mul(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a * *b;
    return 0;
}

static int div(StateHANDLE this, int* a, int* b, int* c)
{
    if (!*b) return DIVIDE_BY_ZERO_ERROR;
    *c = *a / *b;
    return 0;
}

static int and(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a & *b;
    return 0;
}

static int nan(StateHANDLE this, int* a, int* b, int* c)
{
    *c = ~(*a & *b);
    return 0;
}

static int orr(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a | *b;
    return 0;
}

static int nor(StateHANDLE this, int* a, int* b, int* c)
{
    *c = ~(*a | *b);
    return 0;
}

static int xor(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a ^ *b;
    return 0;
}

static int mod(StateHANDLE this, int* a, int* b, int* c)
{
    *c = *a % *b;
    return 0;
}

static int bgt(StateHANDLE this, int* a, int* b, int* c)
{
    if (*a > *b) this->regs[255] = *c;
    return 0;
}

static int beq(StateHANDLE this, int* a, int* b, int* c)
{
    if (*a == *b) this->regs[255] = *c;
    return 0;
}

static int ldr(StateHANDLE this, int* a, int* b, int* c)
{
    if (*a+*b < 0) return NEGATIVE_MEMORY_ACCESS_ERROR;
    if (*a+*b > this->limit) return OUT_OF_MEMORY_ERROR;
    *c = this->mem[*a+*b];
    return 0;
}

static int str(StateHANDLE this, int* a, int* b, int* c)
{
    if (*a+*b < 0) return NEGATIVE_MEMORY_ACCESS_ERROR;
    if (*a+*b > this->limit) return OUT_OF_MEMORY_ERROR;
    this->mem[*a+*b] = *c;
    return 0;
}

static int get(StateHANDLE this, int* a, int* b, int* c)
{
    //TODO
}

static int put(StateHANDLE this, int* a, int* b, int* c)
{
    //TODO
}

int state_step(State s)
{
    int inst;
    int a,b,c;
    int *ar,*br,*cr;
    StateHANDLE this = s;

    if (!this) return false;

    inst = this->mem[this->regs[255]++];

    c = inst & 0xFF;
    inst>>=8;
    b = inst & 0xFF;
    inst>>=8;
    a = inst & 0xFF;
    inst>>=8;
    
    if (a == 254) {
        ar = &(this->mem[this->regs[255]++]);
    } else {
        ar = &(this->regs[a]);
    }

    if (b == 254) {
        br = &(this->mem[this->regs[255]++]);
    } else {
        br = &(this->regs[b]);
    }
    
    if (c == 254) {
        cr = &(this->mem[this->regs[255]++]);
    } else {
        cr = &(this->regs[c]);
    }

    switch (inst) {
        case 0x0: return add(this,ar,br,cr);
        case 0x1: return sub(this,ar,br,cr);
        case 0x2: return mul(this,ar,br,cr);
        case 0x3: return div(this,ar,br,cr);
        case 0x4: return and(this,ar,br,cr);
        case 0x5: return nan(this,ar,br,cr);
        case 0x6: return orr(this,ar,br,cr);
        case 0x7: return nor(this,ar,br,cr);
        case 0x8: return xor(this,ar,br,cr);
        case 0x9: return mod(this,ar,br,cr);
        case 0xA: return bgt(this,ar,br,cr);
        case 0xB: return beq(this,ar,br,cr);
        case 0xC: return ldr(this,ar,br,cr);
        case 0xD: return str(this,ar,br,cr);
        case 0xE: return get(this,ar,br,cr);
        case 0xF: return put(this,ar,br,cr);
        default: //TODO: report error
                  return false;
    }
}
    
    

