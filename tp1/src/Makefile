#Compilateur et options de compilation
CC=gcc
CFLAGS=-Wall -ansi -pedantic

#Fichiers du projet
SOURCES=main.c gestion_news.c liste_news.c
OBJECTS=$(SOURCES:.c=.o)

#Nom du programme
EXECUTABLE=programme

all: $(SOURCES)
	$(CC) $^ -o $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)

