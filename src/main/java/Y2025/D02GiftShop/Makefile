PROG = main

SRC = main.cpp Utils.cpp

CFLAGS = -g -std=c++17

LIBS = 

CC = g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBS)

clean:
	rm -f $(PROG)

.PHONY: all clean