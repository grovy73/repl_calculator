#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static token_t* generate_number_token(char** buffer) {
  int len = strspn(*buffer, "0123456789.");
  char number[len];
  for(int i = 0; i < len; i++) {
    number[i] = buffer[0][i];
  }
  *buffer += len;


  token_t* out = malloc(sizeof(token_t));
  if(strchr(number, '.')) {
    out->type = FLOAT;
    out->value = malloc(sizeof(float));
    if(!out->value) exit(EXIT_FAILURE);

    *(float*)out->value = strtof(number, NULL);
  } else {
    out->type = INTEGER;
    out->value = malloc(sizeof(int));
    if(!out->value) exit(EXIT_FAILURE);
    
    char* endptr;
    *(int*)out->value = strtol(number, &endptr, 10);
    if(endptr == number) {
      puts("No digits");
    }
  }

  return out;
}

size_t lex(token_t* tokens, char* buffer) {
  size_t count = 0;

  token_t* tmp;
  while(*buffer) {
    if(*buffer >= '0' && *buffer <= '9') {
      tmp = generate_number_token(&buffer);
      tokens[count++] = *tmp;
      free(tmp);
    }

    if(*buffer == ' ') {
      buffer++;
      continue;
    }

    if(*buffer == '(') {
      token_t token = {.type = LPAREN, .value = NULL};
      tokens[count++] = token;
      buffer++;
      continue;
    }

    if(*buffer == ')') {
      token_t token = {.type = RPAREN, .value = NULL};
      tokens[count++] = token;
      buffer++;
      continue;
    }

    if(*buffer == '+' || *buffer == '-' || *buffer == '/' || *buffer == '*') {
      token_t token = {.type = OPERATOR};
      token.value = malloc(sizeof(char));
      *(char*)token.value = *buffer;
      tokens[count++] = token;
    }

    buffer++;
  }
 
  return count;
}

void print_tokens(token_t* tokens, size_t n) {
  for(size_t i = 0; i < n; i++) {
    switch(tokens[i].type) {
      case INTEGER:
        printf("INTEGER: %d\n", *(int*)tokens[i].value);
        break;
      case FLOAT:
        printf("FLOAT: %f\n", *(float*)tokens[i].value);
        break;
      case OPERATOR:
        printf("OPERATOR: %c\n", *(char*)tokens[i].value);
        break;
      case LPAREN:
        printf("LPAREN\n");
        break;
      case RPAREN:
        printf("RPAREN\n");
        break;
      default:
        printf("WHAT DA HELLY\n");
        break;
    }
  }
}
