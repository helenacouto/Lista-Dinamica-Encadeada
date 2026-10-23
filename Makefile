CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

lista06: main.c ListaTarefas.c ListaTarefas.h
	$(CC) $(CFLAGS) main.c ListaTarefas.c -o lista05

run: lista06
	./lista06

valgrind: lista06
	valgrind --leak-check=full --show-leak-kinds=all ./lista05

clean:
	rm -f lista05
