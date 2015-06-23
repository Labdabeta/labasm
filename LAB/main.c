#include <stdio.h>
#include "emulate.h"

#define HELP_MESSAGE (\
        "LAB [executable]\n"\
        "\tRuns the specified executable file on a simulated LAB machine.")

int main(int argc, char *argv[])
{
    if (argc!=2)
        return printf(HELP_MESSAGE),1;


    return 0;
}
