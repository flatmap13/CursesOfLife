CC=gcc

life: life.c
	$(CC) life.c -o life -lncurses
