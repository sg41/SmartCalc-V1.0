#ifndef SRC_RPR_EXPR_H_
#define SRC_RPR_EXPR_H_

#define OPERAND 0
#define OPERATOR 1
#define UNARYOPERATOR 2
#define VARIABLE 3
#define L_BRACKET 4
#define R_BRACKET 5
#define FUNCTION 6

#define ADD_SCORE 1
#define SUB_SCORE 1
#define MULT_SCORE 2
#define DIV_SCORE 2
#define EXP_SCORE 3
#define L_SCORE 6
#define R_SCORE 6
#define U_SCORE 5

struct expr {
  unsigned int length;
  struct ll_node *head;
};

struct expr *expr_new(void);
void expr_destroy(struct expr **e);
void expr_add_symbol(struct expr *e, const unsigned int s, const double d);
void expr_print(const struct expr *e);
struct expr *expr_shunt(const struct expr *e);
struct expr *expr_from_array(const char *a);
char *one_expr_from_string(char *prog, struct expr **infix_to_fill, int *good,
                           int *parents);
struct expr *expr_from_string(char *a, int *good);

#endif  // SRC_RPR_EXPR_H_
