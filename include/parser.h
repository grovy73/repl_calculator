#ifndef PARSER_H
#define PARSER_H
#include <stddef.h>
#include "lexer.h"

void parse(token_t* tokens, size_t count);

#endif
