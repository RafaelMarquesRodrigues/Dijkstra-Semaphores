#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int shouldConsumeProduct(){
	return rand()%100 < 40 ? 1 : 0;
}

void removeProduct(){
	buffer[full] = 0;
}

void decreaseFull(){
	while(full == 0){
		printf("CONSUMER: No products. Waiting...\n");
		pthread_cond_wait(&condConsumer, &mutex);
	}

	full--;

	printf("CONSUMER: Got my product !\n");
	printf("CONSUMER: Full space %d\n", full);
}

void increaseEmpty(){
	empty++;
	
	//signals the producer the buffer is not full
	pthread_cond_signal(&condProducer);

	printf("CONSUMER: Empty space %d\n", empty);
}

void *runConsumer(){
	srand(time(NULL));

	while(TRUE){
		if(shouldConsumeProduct()){
			down("consumer");

			//all changes to shared content is made while the mutex is locked
			decreaseFull();
			removeProduct();
			increaseEmpty();

			sleep(2);
			up("consumer");
		}
	}

	pthread_exit(NULL);
}
