#include "parser.h"
#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define IN_PAREN_FLAG 1


float parse_term(token_t* tokens, size_t count, size_t current_index, unsigned char flags) {
  if(current_index >= count) return 0;

  float sum = 0;
  switch(tokens[current_index].type) {
    case OPERATOR:
      fprintf(stderr, "Syntax error\n");
      exit(EXIT_FAILURE);
    case INTEGER:
      sum += (float)*(int*)tokens[current_index].value;
      break;
    case FLOAT:
      sum += *(float*)tokens[current_index].value;
      break;
    case LPAREN:
      current_index++;
      sum += parse_term(tokens, count, current_index, flags | IN_PAREN_FLAG);
      break;
    case RPAREN:
      if(flags & IN_PAREN_FLAG) {
        return sum;
      } else {
        fprintf(stderr, "Syntax error\n");
        exit(EXIT_FAILURE);
      }
  }
  current_index++;
  if(current_index >= count) return sum;

  switch(tokens[current_index].type) {
    case OPERATOR:
      switch(*(char*)tokens[current_index].value) {
        case '+':
        case '-':
          return sum;
        case '*':
          sum *= parse_term(tokens, count, current_index + 1, flags);
          break;
        case '/':
          sum /= parse_term(tokens, count, current_index + 1, flags);
          break;
        default:
          fprintf(stderr, "Unknown operator\n");
          exit(EXIT_FAILURE);

      }
      break;
    default:
      fprintf(stderr, "Syntax error\n");
      exit(EXIT_FAILURE);
  }
  return sum;
}

void parse(token_t* tokens, size_t count) {
  size_t current_index = 0;
  float result = parse_term(tokens, count, current_index, 0);
  while(current_index < count) {
    if(tokens[current_index].type == OPERATOR && *(char*)tokens[current_index].value == '+') {
      result += parse_term(tokens, count, current_index + 1, 0);
    } else if(tokens[current_index].type == OPERATOR && *(char*)tokens[current_index].value == '-') {
      result -= parse_term(tokens, count, current_index + 1, 0);
    }
    current_index++;
  }
  printf("%f\n", result);
}
