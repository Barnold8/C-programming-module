CC=gcc
CFLAGS=-g
CLIBS=
OBJS=obj/dijkstra.o obj/graph.o obj/linked_list.o
PORT=4242

all: server

# libraries

server: server.c  
	$(CC) -o server $^ $(CFLAGS) $(OBJS) $(CLIBS)

server_memcheck: server 
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./server $(PORT)

clean:
	rm -f server *.o
