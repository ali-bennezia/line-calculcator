#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256
#define MAX_LINE_TOKENS 10

int interpret_line( char *buff )
{
    char *tokens[ MAX_LINE_TOKENS ] = { 0 };
    size_t tok_count = 0;

    char *tok = strtok( buff, " \n\r\t" );
    while ( tok != NULL && tok_count < MAX_LINE_TOKENS ){
        size_t tok_len = strlen( tok );
        char *tok_cpy = malloc( tok_len + 1 );
        strcpy( tok_cpy, tok );
        tokens[ tok_count ] = tok_cpy;

        ++tok_count;
        tok = strtok( NULL, " \n\r\t" );
    }

    printf( "Tokens:\n" );
    for ( size_t i = 0; i < tok_count; ++i )
    {
        printf( "%s\n", tokens[ i ] );
    }

    return ( tok_count >= MAX_LINE_TOKENS );
}

int read_file( const char *path )
{
    FILE *f = fopen( path, "rb" );
    if ( f == NULL ){
        fprintf( stderr, "Error, couldn't open file: %s\n", strerror( errno ) );
        return 1;
    }

    char line[ MAX_LINE_LENGTH + 1 ] = { 0 };

    while ( fgets( line, MAX_LINE_LENGTH, f ) )
    {
        interpret_line( line );
    }

    if ( fclose( f ) )
    {
        fprintf( stderr, "Error, couldn't close file: %s\n", strerror( errno ) );
        return 1;
    }

    return 0;
}