#ifndef SRC_RPR_EXPR_H_
#define SRC_RPR_EXPR_H_

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
char *one_expr_from_string(char *prog, struct expr **infix_to_fill, int *good, int *parents);
struct expr *expr_from_string(char *a, int *good);

#endif  // SRC_RPR_EXPR_H_

