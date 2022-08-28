LDOPTS =  
CCOPTS = -Wall -Werror -Wextra -DDEBUG=0
ROOT := $(shell git rev-parse --show-toplevel)

TARGET1 = $(ROOT)/build/graph

TARGETS = $(TARGET1)

OBJECT1 = graph.o rpr/llist.o rpr/stack.o rpr/expr.o rpr/core.o

OBJECTS = $(OBJECT1)
SOURCES = $(OBJECTS:.o=.c)
HEADERS = $(OBJECTS:.o=.h)

all:  graph clean

graph: $(TARGET1)
	gcc $(LDOPTS) -o $(TARGET1) $(OBJECT1) -lm

$(TARGET1): $(OBJECT1)

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
	rm -rf $(OBJECTS) $(OBJECTS:.o=.c.bak)

rebuild: clean all

