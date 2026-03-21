#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256
#define MAX_LINE_TOKENS 10

#include "tokens.h"

#include "utils.h"

int interpret_line( char *buff )
{
    unsigned int result = 0;

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

    if ( tok_count <= 0 ){
        result = 0;
        goto cleanup;
    }

    if ( tok_count == MAX_LINE_TOKENS && tok != NULL ) {
        fprintf( stderr, "Error: exceeded maximum amount of tokens in a line.\n" );
        result = 1;
        goto cleanup;
    }

    int (*exec_function)(char**, unsigned int) = NULL;
    int match_r = match_token( tokens, tok_count, &exec_function );
    if ( match_r || exec_function == NULL ) {
        result = 1;
        goto cleanup;
    }

    result = exec_function( tokens + 1, ( unsigned int )( tok_count - 1 ) );

    cleanup:
    free_tokens( tokens, tok_count );
    return result;
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