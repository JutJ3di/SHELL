all: shell

shell: main.c
	gcc -o shell main.c

clean:
	rm -rf *.o
	rm -rf shell
