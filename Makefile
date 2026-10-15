CC = gcc
CFLAGS = -Wall -Wextra -std=c11

test: test.o solve.o
	$(CC) $(CFLAGS) $^ -o $@

test.debug: test.debug.o solve.debug.o
	$(CC) $(CFLAGS) -g -DDEBUG $^ -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

solve.o: solve.c
	$(CC) $(CFLAGS) -c $< -o $@

test.debug.o: test.c
	$(CC) $(CFLAGS) -g -DDEBUG -c $< -o $@

solve.debug.o: solve.c
	$(CC) $(CFLAGS) -g -DDEBUG -c $< -o $@

debug: test.debug

clean:
	rm -f *.o test test.debug

.PHONY: clean debug
