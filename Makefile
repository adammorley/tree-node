CC=clang
CFLAGS=-I. -g
DEPS=../log/log.c ../queue/queue.c

all: test

clean:
	rm -f test *.o

test: test.c tree_node.c $(DEPS)
	$(CC) -o test test.c tree_node.c $(DEPS) $(CFLAGS)
