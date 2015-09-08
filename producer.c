#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//40% of chance to create a product
int shouldCreateProduct(){
	return rand()%100 < 80 ? 1 : 0;
}

int createProduct(){
	return 1;
}

void decreaseEmpty(){
	//if the buffer is full, waits until its empty to produce more
	while(full == MAX_BUFFER){
		printf("PRODUCER: Buffer is max. Waiting...\n");
		pthread_cond_wait(&condProducer, &mutex);
	}
	
	empty = empty - 1;
	
	printf("PRODUCER: Created my product !\n");
	printf("PRODUCER:Empty space %d\n", empty);
}

void increaseFull(){
	full++;
	printf("PRODUCER: Full space %d\n", full);
	pthread_cond_signal(&condConsumer);
}

void *runProducer(){
	srand(time(NULL));
	int product;

	while(TRUE){
		if(shouldCreateProduct()){
			down("producer");

			//all changes to shared content is made while the mutex is locked
			decreaseEmpty();
			product = createProduct();
			buffer[full + 1] = product;
			increaseFull();	

			sleep(2);
			up("producer");
		}
	}

	pthread_exit(NULL);
} 