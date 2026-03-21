#include "utils.h"

#include <stdlib.h>
#include <stddef.h>

void free_tokens( char **toks, unsigned int size )
{
    for ( size_t i = 0; i < size; ++i ){
        free( *toks );
        ++toks;
    }
}