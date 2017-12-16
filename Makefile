TARGETS = test
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib




checkers : constructmaps.c linkedlist.o
	gccx -o checkers constructmaps.c linkedlist.o -lm

linkedlist.o : linkedlist.c checkers.h
	gccx -c -o linkedlist.o linkedlist.c -lm



all: $(TARGETS)

test:
	g++ -o test test.cpp $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LFLAGS) $(CFLAGS)

clean:
	rm -f $(TARGETS) *.o *~ checkers linkedlist *.o *~


