#include "tokens.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "routines.h"

static char* op_keywords[] = {
    "echo"
};

static int (*exec_funcs[])(char**, unsigned int) = {
    exec_echo_rout
};

static const size_t keywords_amount = sizeof( op_keywords ) / sizeof( char* );

int match_token( char **line_toks, unsigned int line_toks_amount, int (**exec_func_out)(char**, unsigned int) )
{
    if ( line_toks_amount <= 0 ) return 0;
    for ( size_t i = 0; i < keywords_amount; ++i )
    {
        if ( strcmp( line_toks[ 0 ], op_keywords[ i ] ) == 0 ){
            *exec_func_out = exec_funcs[ i ];
            return 0;
        }
    }
    fprintf(stderr, "Error: token '%s' does not correspond to any known keyword.\n", line_toks[0]);
    return 1;
}  