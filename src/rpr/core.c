#include "core.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

double expo(const double base, const double power) {
  double result;
  if (power < 0) {
    result = 0;
  } else {
    double res = 1;
    for (int i = 0; i < power; i++) {
      res *= base;
    }
    result = res;
  }
  return result;
}

double rpn_reduce(const struct expr *e, double x) {
  struct stk *k = stk_new();
  double a, b;
  double op;
  for (struct ll_node *i = e->head; i != NULL; i = i->next) {
    if (i->state == OPERAND) {
      stk_push(k, i->state, i->datum);
    } else if (i->state == VARIABLE) {
      stk_push(k, i->state, x);
    } else {
      if (i->state == OPERATOR) {
        b = stk_peek(k);
        stk_pop(k);
      }
      a = stk_peek(k);
      stk_pop(k);
      op = i->datum;
      switch ((char)op) {
        case '+':
          stk_push(k, OPERAND, a + b);
          break;
        case '-':
          stk_push(k, OPERAND, a - b);
          break;
        case '*':
          stk_push(k, OPERAND, a * b);
          break;
        case '/':
          stk_push(k, OPERAND, a / b);
          break;
        case '^':
          stk_push(k, OPERAND, expo(a, b));
          break;
        case 'm':
          stk_push(k, OPERAND, -a);
          break;
        case 'p':
          stk_push(k, OPERAND, a);
          break;
        case 's':
          stk_push(k, OPERAND, sin(a));
          break;
        case 'c':
          stk_push(k, OPERAND, cos(a));
          break;
        case 't':
          stk_push(k, OPERAND, tan(a));
          break;
        case 'g':
          stk_push(k, OPERAND, tan(3.14 / 2 - a));
          break;
        case 'q':
          stk_push(k, OPERAND, sqrt(a));
          break;
        case 'l':
          stk_push(k, OPERAND, log(a));
          break;
        case 'a':
          stk_push(k, OPERAND, fabs(a));
          break;
        default:
          break;
      }
    }
  }
  double res = stk_peek(k);
  stk_destroy(&k);
  return res;
}
