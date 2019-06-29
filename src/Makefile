CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include
PROGRAM       = c-webserv

.PHONY: all
all: main

main: main.o response.o route.o
	gcc -o $(PROGRAM) main.o response.o route.o $(CFLAGS)

main.o: main.c
	gcc -c main.c

response.o: response.c
	gcc -c response.c

route.o: route.c
	gcc -c route.c

.PHONY: clean
clean:
	rm -rf *.o $(PROGRAM)
