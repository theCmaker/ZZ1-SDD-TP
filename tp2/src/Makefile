#Compilateur et options de compilation
CC=gcc
CFLAGS=-Wall -ansi -pedantic -Wextra -g

#Fichiers du projet
SOURCES=main.c stack.c truc.c
OBJECTS=$(SOURCES:.c=.o)

EXEC=prog

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm $(OBJECTS) $(EXEC)

