#ifndef __TOKENS_H__
#define __TOKENS_H__

int match_token( char **line_toks, unsigned int line_toks_amount, int (**exec_func_out)(char**, unsigned int) );

#endif