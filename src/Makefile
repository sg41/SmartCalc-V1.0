LDOPTS = -L. -lm -lcheck
CCOPTS = -Wall -Werror -Wextra -DDEBUG=0
CC=gcc
APP_ARGS="sin(cos(x^2)^(1*-100))*x"
TEST_APP=test.app
TEST_C=tests/test.c

ROOT := $(shell git rev-parse --show-toplevel)
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	LEAKS=CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes 
else
	LIBS=-lcheck
	LEAKS=CK_FORK=no leaks --atExit -- 
endif

APP = $(ROOT)/build/graph
LIB = s21_SmartCalc
SRC_DIR=$(ROOT)/src
OBJECTS = rpr/llist.o rpr/stack.o rpr/expr.o rpr/core.o
SOURCES = $(OBJECTS:.o=.c)
HEADERS = $(OBJECTS:.o=.h)

all:  graph 

$(LIB): $(OBJECTS)
	ar rcs lib$(LIB).a $(OBJECTS)

graph: $(LIB) graph.c graph.h rpr/llist.h rpr/stack.h
	[ -d ../build ] || mkdir ../build
	gcc $(CCOPTS) graph.c -o $(APP) -l$(LIB) $(LDOPTS)

$(APP): graph

graph.o: graph.c graph.h rpr/llist.h
	gcc $(CCOPTS) $(LDOPTS) -c graph.c

rpr/llist.o: rpr/llist.c rpr/llist.h graph.h
	gcc $(CCOPTS) $(LDOPTS) -c rpr/llist.c -o rpr/llist.o

rpr/stack.o: rpr/stack.c rpr/stack.h
	gcc $(CCOPTS) $(LDOPTS) -c rpr/stack.c -o rpr/stack.o

rpr/expr.o: rpr/expr.c rpr/expr.h
	gcc $(CCOPTS) $(LDOPTS) -c rpr/expr.c -o rpr/expr.o

rpr/core.o: rpr/core.c rpr/core.h
	gcc $(CCOPTS) $(LDOPTS) -c rpr/core.c -o rpr/core.o

$(TEST_C): tests/*.check
	checkmk tests/*.check > $(TEST_C)

test: $(TEST_C) $(LIB)
	$(CC) $(CCOPTS) $(TEST_C) -o test.app $(LDOPTS) $(LIBS) -l$(LIB)
	-./$(TEST_APP)

check: $(SOURCES)
	cp $(ROOT)/materials/linters/CPPLINT.cfg ./
	sed -i".bak" "s/\t/    /g" $(SOURCES)
	sed -i".bak" "s/[ \t]*$$//g" $(SOURCES)
	python3 $(ROOT)/materials/linters/cpplint.py --extensions=c $(SOURCES)
	python3 $(ROOT)/materials/linters/cpplint.py --extensions=c $(HEADERS)

check2: $(SOURCES)
	cppcheck --enable=all --suppress=missingIncludeSystem $(ROOT)/src/

.PHONY: all clean rebuild

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.c.bak) $(APP) lib$(LIB).a $(TEST_APP) $(TEST_C)
	rm -rf *.o $(TEST_APP) lib$(LIB).a $(OBJECTS) *.a *.gcno *.gcda *.gcov *.info

rebuild: clean all

leaks: $(APP)
	$(LEAKS) $(APP) $(APP_ARGS)

leaks_test: test
	$(LEAKS) ./$(TEST_APP) $(APP_ARGS)

gcov_report: clean $(TEST_C)
	$(CC) $(CCOPTS) --coverage -c $(SOURCES)
	ar rc lib$(LIB).a *.o
	$(CC) $(CCOPTS) $(TEST_C) -L./ -l$(LIB) $(LIBS) -lgcov -o $(TEST_APP)
	$(CLEAN) $(OBJ)
	-./$(TEST_APP)
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	[ -d $(ROOT)/src/report ] || mkdir $(ROOT)/src/report
	genhtml -o $(ROOT)/src/report gcov_report.info
	rm -rf *.o $(TEST_APP) lib$(LIB).a $(OBJECTS) *.a *.gcno *.gcda *.gcov *.info $(TEST_C)