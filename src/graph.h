#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#define MAXSTR 10000

#define D(fmt, ...)                      \
  do {                                   \
    if (DEBUG) {                         \
      fprintf(stderr, fmt, __VA_ARGS__); \
    }                                    \
  } while (0)

#define MINX -3
#define MAXX 3  // 4 * 3.14
#define MINY -3
#define MAXY 3
#define MAXI 80
#define MAXJ 25
#define MIDDLEJ 13

#endif  // SRC_GRAPH_H_
