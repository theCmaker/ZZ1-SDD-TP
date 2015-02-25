#Compilateur et options de compilation
CC=gcc
CFLAGS=-Wall -ansi -pedantic -Wextra -g

#Fichiers du projet
SOURCES=main.c gestion_news.c liste_news.c
OBJECTS=$(SOURCES:.c=.o)

#Nom du programme
EXEC=programme

all: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(EXEC)

.c.o:
	$(CC) -c $(CFLAGS) $*.c
clean:
	rm $(OBJECTS) $(EXEC)

