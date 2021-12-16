CC=gcc
FLAGS= -Wall 

all: stringProg

stringProg: main.o word_lib.a 
	$(CC) $(FLAGS) -o stringProg main.o word_lib.a 

word_lib.a: word_lib.o
	ar rcs word_lib.a word_lib.o

word_lib.o: word_lib.c word_lib.h
	$(CC) $(FLAGS) -c word_lib.c

main.o: main.c word_lib.h
	$(CC) $(FLAGS) -c main.c

.PHONY: clean

clean: 
	rm -rf *.o *.a stringProg

