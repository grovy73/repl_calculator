#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

#define BUFFER_SIZE 256

int main(void) {

  char buffer[BUFFER_SIZE];
  // REPL Loop
  for (;;) {
    printf(">> ");
    fflush(stdout);
    fgets(buffer, BUFFER_SIZE, stdin);

    token_t tokens[MAX_TOKENS];
    size_t len = lex(tokens, buffer);
    // print_tokens(tokens, len);

    parse(tokens, len);
  }

  return 0;
}
