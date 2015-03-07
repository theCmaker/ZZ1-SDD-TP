#Compilateur et options de compilation
CC=gcc
CFLAGS=-Wall -ansi -pedantic -Wextra -g

#Fichiers du projet
SOURCES1=main.c stack.c
SOURCES2=truc.c stack.c
OBJECTS1=$(SOURCES1:.c=.o)
OBJECTS2=$(SOURCES2:.c=.o)

#Nom du programme
EXEC1=prog
EXEC2=truc

all: $(EXEC1) $(EXEC2)
    

$(EXEC1): $(OBJECTS1)
	$(CC) $(CFLAGS) $^ -o $(EXEC1)

$(EXEC2): $(OBJECTS2)
	$(CC) $(CFLAGS) $^ -o $(EXEC2)

.c.o:
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm $(OBJECTS1) $(EXEC1) $(EXEC2) truc.o

