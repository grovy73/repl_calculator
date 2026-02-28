#ifndef LEXER_H
#define LEXER_H
#define MAX_TOKENS 128
#include <stddef.h>

typedef enum {
  INTEGER,
  FLOAT,
  OPERATOR,
  LPAREN,
  RPAREN,
} token_type;

typedef struct {
  token_type type;
  void* value;
} token_t;

size_t lex(token_t* tokens, char* buffer);
void print_tokens(token_t* tokens, size_t n);

#endif
