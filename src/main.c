#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"

int main ( int argc, char **argv )
{
    if ( argc == 2 ){
        const char* path = *( argv + 1 );
        read_file( path );
    }
    
    return EXIT_SUCCESS;
}