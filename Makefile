all: 
	gcc -g -o main main.c -pthread -Wall

run:
	./main

clean:
	rm *.o main
