all: main

main: bst.o main.o
	gcc -g bst.o main.o -o main
bst.o:  bst.h bst.c
	gcc -c -g bst.c -o bst.o
main.o: bst.h main.c
	gcc -c -g main.c -o main.o
run: all
	./main
checkmem: all
	valgrind -v ./main
clean:
	rm -f bst.o main.o main
