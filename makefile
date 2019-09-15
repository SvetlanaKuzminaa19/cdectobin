all: main.c
	gcc main.c -o main -lncurses
clean:
	rm -rf *.o hello