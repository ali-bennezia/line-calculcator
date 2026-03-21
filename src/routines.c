#include "routines.h"

#include <stdlib.h>
#include <stdio.h>

int exec_echo_rout( char **args, unsigned int args_count )
{
    for ( size_t i = 0; i < args_count; ++i ){
        printf("%s ", *args);
        ++args;
    }
    printf("\n");
    return 0;
}