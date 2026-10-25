CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaDinEncadeada.o main.o
	$(CC) $(CFLAGS) -o teste ListaDinEncadeada.o main.o

ListaDinEncadeada.o: ListaDinEncadeada.c ListaDinEncadeada.h
	$(CC) $(CFLAGS) -c ListaDinEncadeada.c

main.o: main.c ListaDinEncadeada.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste