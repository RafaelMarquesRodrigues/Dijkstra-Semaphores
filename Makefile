all: resources.o consumer.o producer.o
	gcc -g -o main resources.o consumer.o producer.o main.c -pthread -Wall

resources.o: resources.c
	gcc -g -c resources.c -Wall

consumer.o: consumer.c
	gcc -g -c consumer.c -Wall

producer.o: producer.c
	gcc -g -c producer.c -Wall

run:
	./main

clean:
	rm *.o main