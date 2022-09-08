#ifndef SRC_GTK_H_
#define SRC_GTK_H_

#include "graph.h"
#include "rpr/core.h"
#include "rpr/expr.h"

typedef struct {
  int iteration;
  char str[MAXSTR];
  double x;
  char error_message[MAXSTR];
  int error;
} calc_data;

void init_calc_data(calc_data *d);
#endif  // SRC_GTK_H_