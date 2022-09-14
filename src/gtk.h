#ifndef SRC_GTK_H_
#define SRC_GTK_H_

#include <assert.h>

#include "graph.h"
#include "rpr/core.h"
#include "rpr/expr.h"

typedef struct {
  int iteration;
  char str[MAXSTR];
  double x;
  char error_message[MAXSTR];
  int error;
  double clip_x1;
  double clip_y1;
  double clip_x2;
  double clip_y2;
} calc_data;

#ifndef MINX
#define MINX -3
#define MAXX 3  // 4 * 3.14
#define MINY -1
#define MAXY 1
#endif

#define VERY_MIN_X -1000000
#define VERY_MAX_X 1000000
#define VERY_MIN_Y -1000000
#define VERY_MAX_Y 1000000

#ifndef EPS
#define EPS 1e-7
#endif

void init_calc_data(calc_data *d);
#endif  // SRC_GTK_H_