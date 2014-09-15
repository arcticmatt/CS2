CC = g++
CFLAGS = -Wall -ansi -pedantic -ggdb
LIBS = -lncurses -lpthread

.PHONY: clean

philosophers: philosophers.cpp
	$(CC) $(CFLAGS) philosophers.cpp -lpthread -lncurses -o philosophers

clean:
	rm -f *.o philosophers

