CC=gcc
CFLAGS=-Wall -ansi -pedantic-errors -g
CLIBS=
OBJS=obj/graph.o obj/linked_list.o

TASK_TEST=3 1:3:1 1:5:2 2:3:10 2:4:2 3:4:2

all: comp1006_test

# libraries

comp1006_test: comp1006_test.c dijkstra.c 
	$(CC) -o comp1006_test $^ $(CFLAGS) $(OBJS) $(CLIBS)

comp1006_test_run: comp1006_test
	./comp1006_test $(TASK_TEST)

comp1006_test_memcheck: comp1006_test
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./comp1006_test $(TASK_TEST)

clean:
	rm -f comp1006_test *.o
