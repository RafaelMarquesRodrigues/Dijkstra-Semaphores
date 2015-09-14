#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void createProduct(){
	buffer++;
}

void pdown(){
	full++;
}

void pup(){
	empty--;

	if(cQueueSize > 0){
		cQueueSize--;
		printf("waking up consumer\n");
		pthread_cond_signal(&cQueue[cQueueSize]);
	}
}

void *runProducer(){
	while(TRUE){
			pthread_mutex_lock(&mutex);
			
			while(full == MAX_BUFFER){
				pQueueSize++;
				printf("producer waiting\n");
				pthread_cond_wait(&pQueue[pQueueSize - 1], &mutex);
				printf("producer released\n");
			}
			
				pdown();

				bufferInUse++;
				createProduct();
				bufferInUse--;
				printf("producer %d %d\n", full, empty);
				
				pup();	
			pthread_mutex_unlock(&mutex);
		}

	pthread_exit(NULL);
} 