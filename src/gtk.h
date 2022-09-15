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
  double amount;
  int duration;
  double rate;
  double monthly_payment;
  double overpayment;
  double total_payment;
  int type;
  int round;
} calc_data;

#define ANNUITET 0
#define DIFFERENTIATED 1

#define DEFAULT_DURATION 12
#define DEFAULT_AMOUNT 100000
#define DEFAULT_RATE 9.5

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