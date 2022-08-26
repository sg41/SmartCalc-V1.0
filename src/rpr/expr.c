#include "expr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define ADD_SCORE 1
#define SUB_SCORE 1
#define MULT_SCORE 2
#define DIV_SCORE 2
#define EXP_SCORE 3
#define L_SCORE 4
#define R_SCORE 4
#define U_SCORE 5

/* Возвращает значение ИСТИНА, если с является оператором. */
int is_oper(char c) {
    return (strchr("+-/*%^()", c)) ? 1 : 0;
}

/* Возвращает значение ИСТИНА, если с является раздилителем. */
int is_space(char c) {
    return (strchr(" \t\n\r", c)) ? 1 : 0;
}

/* Возвращает значение ИСТИНА, если с является раздилителем, в том числе оператором. */
int is_delim(char c) {
    return (strchr("+-/*%^()", c) || is_space(c)) ? 1 : 0;
}

/* Возвращает значение ИСТИНА, если с является цифрой или точкой */
int is_digit(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

/* Возвращает значение ИСТИНА, если с является буквой */
int is_alpha(char c) {
    return c >= 'A' && c <= 'z';
}

struct expr *expr_new(void) {
    struct expr *e = malloc(sizeof(*e));
    e->length = 0;
    e->head = NULL;
    return e;
}

void expr_destroy(struct expr **e) {
    struct ll_node *tmp;
    for (struct ll_node *i = (*e)->head; i != NULL; i = tmp) {
        tmp = i->next;
        ll_node_destroy(&i);
        (*e)->length--;
    }
    free(*e);
    (*e) = NULL;
}

void expr_add_symbol(struct expr *e, const unsigned int s, const double d) {
    if (e->length > 0) {
        ll_node_append(e->head, s, d);
    } else {
        e->head = ll_node_new(s, d);
    }
    (e->length)++;
}

unsigned int precedence(const struct ll_node *n) {
    unsigned int score;
    if (n != NULL) {
        switch ((char)n->datum) {
            case '+':
                score = ADD_SCORE;
                break;
            case '-':
                score = SUB_SCORE;
                break;
            case '*':
                score = MULT_SCORE;
                break;
            case '/':
                score = DIV_SCORE;
                break;
            case '^':
                score = EXP_SCORE;
                break;
            case '(':
                score = L_SCORE;
                break;
            case ')':
                score = R_SCORE;
                break;
            case 's':
            case 'c':
            case 't':
            case 'g':
            case 'q':
            case 'l':
                score = EXP_SCORE;
                break;
            case 'p':
            case 'm':
                score = U_SCORE;
                break;
            default:
                break;
        }
    } else {
        score = 0;
    }
    return score;
}

void change_stack(struct expr *rpn, struct stk *opstack) {
    expr_add_symbol(rpn, stk_peek_status(opstack), stk_peek(opstack));
    stk_pop(opstack);
}
struct expr *expr_shunt(const struct expr *e) {
    struct stk *opstack = stk_new();
    struct expr *rpn = expr_new();
    for (struct ll_node *i = e->head; i != NULL; i = i->next) {
        if (i->state == OPERAND) {  // Если это число
            expr_add_symbol(rpn, OPERAND, i->datum);
        } else if (i->state == VARIABLE) {  // Если это переменная
            expr_add_symbol(rpn, VARIABLE, i->datum);
        } else if ((i->state == OPERATOR) && (i->datum == '(')) {  // Если это скобка открылась
            stk_push(opstack, OPERATOR, i->datum);
        } else if ((i->state == OPERATOR) && (i->datum == ')')) {  // Если скобка закрылась
            while (stk_peek(opstack) != '(')
                change_stack(rpn, opstack);
            stk_pop(opstack);
        } else {  // Если это оператор
            while ((opstack->depth > 0) &&
                   ((precedence(opstack->top) > precedence(i)) ||
                    ((precedence(opstack->top) == precedence(i)) && !(i->datum != '^'))) &&
                   (opstack->top->datum != '('))
                change_stack(rpn, opstack);
            stk_push(opstack, i->state, i->datum);
        }
    }
    while (opstack->depth > 0)
        change_stack(rpn, opstack);
    stk_destroy(&opstack);
    return rpn;
}

double get_operand(const char *a) {
    char buff[11] = "9999999999";
    char *b = buff;
    // int sign = 1;
    if (*a == '-' || *a == '+') {
        *b = *a;
        a++;
        b++;
    }
    while ((*a != '\0') && (((*a >= '0') && (*a <= '9')) || (*a == '.'))) {
        *b = *a;
        b++;
        a++;
    }
    *b = '\0';
    return atof(buff);
}

struct expr *expr_from_string(char *a, int *good) {
    char *p = a;
    struct expr *infix = NULL;
    int parents = 0;
    if (p && *p) {
        p = one_expr_from_string(p, &infix, good, &parents);
        while (*p) {
            p = one_expr_from_string(p, &infix, good, &parents);
        }
    }
    if (parents != 0) *good = 0;
    return infix;
}

char *check_f(struct expr *infix, char *prog, int *good) {
    if (strncmp(prog, "sin", 3) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 's');
        prog += 3;
    } else if (strncmp(prog, "cos", 3) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 'c');
        prog += 3;
    } else if (strncmp(prog, "tan", 3) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 't');
        prog += 3;
    } else if (strncmp(prog, "ctg", 3) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 'g');
        prog += 3;
    } else if (strncmp(prog, "sqrt", 4) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 'q');
        prog += 4;
    } else if (strncmp(prog, "ln", 2) == 0) {
        expr_add_symbol(infix, UNARYOPERATOR, 'l');
        prog += 2;
    } else if (*prog == 'x' || *prog == 'X') {
        expr_add_symbol(infix, VARIABLE, 'x');
        prog++;
    } else {
        while (prog && *prog && !is_delim(*prog)) {
            prog++;
        }
        *good = 0;
    }
    return prog;
}

char *one_expr_from_string(char *str, struct expr **infix_to_fill, int *good, int *parents) {
    struct expr *infix;
    char *prog = str;

    if (*infix_to_fill == NULL) {
        infix = expr_new();
    } else {
        infix = *infix_to_fill;
    }

    if (prog && *prog) {
        while (*prog && is_space(*prog)) ++prog;  // Skip spaces
        if ((*prog == '+') || (*prog == '-')) {
            if (*(prog + 1) && (is_alpha(*(prog + 1)) || *(prog + 1) == '(')) {
                expr_add_symbol(infix, OPERAND, (*prog == '-') ? -1 : 1);
                expr_add_symbol(infix, OPERATOR, '*');
                prog++;
            } else {
                expr_add_symbol(infix, OPERATOR, *prog);
                expr_add_symbol(infix, OPERAND, get_operand(prog));
                prog++;
                while (*prog && is_digit(*prog)) {
                    prog++;
                }
            }
        } else if (is_oper(*prog)) {
            if (*prog == '(') (*parents)++;
            if (*prog == ')') (*parents)--;
            expr_add_symbol(infix, OPERATOR, *prog);
            prog++;
        } else if (is_alpha(*prog)) {
            prog = check_f(infix, prog, good);
        } else if (is_digit(*prog)) {
            expr_add_symbol(infix, OPERAND, get_operand(prog));
            while (*prog && is_digit(*prog)) {
                prog++;
            }
        }
    }
    *infix_to_fill = infix;
    return prog;
}
