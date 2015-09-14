#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void removeProduct(){
	buffer--;
}

void cdown(){
	full--;
}

void cup(){
	empty++;

	if(pQueueSize > 0){
		pQueueSize--;
		printf("waking up producer\n");
		pthread_cond_signal(&pQueue[pQueueSize]);
	}
}

void *runConsumer(){
	while(TRUE){
			pthread_mutex_lock(&mutex);

			while(full == 0){
				cQueueSize++;
				printf("consumer waiting\n");
				pthread_cond_wait(&cQueue[cQueueSize - 1], &mutex);
				printf("consumer ok\n");
			}
				cdown();

				bufferInUse++;
				removeProduct();
				bufferInUse--;
				printf("consumer %d %d\n", full, empty);
				
				cup();
			pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}
