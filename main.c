#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "resources.h"
#include "consumer.h"
#include "producer.h"

//function to check if there is, in a given moment, more than 1 thread in the same critical region
void *runCheck(){
	while(TRUE){
		if(bufferInUse > 1)
			printf("Critical region problem\n");
	}
}

int main(int argc, char *argv[]){
	pthread_t p[MAX_PRODUCERS];
	pthread_t c[MAX_CONSUMERS];
	pthread_t checker;
	long t = 0;
	void *status;
	int i;

	//initializes the mutex
	pthread_mutex_init(&mutex, NULL);
	
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_cond_init(&cQueue[i], NULL);
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_cond_init(&pQueue[i], NULL);

	//initializes the funcion to check for critical access problem
	pthread_create(&checker, NULL, runCheck, (void *) t);

	//creates and initializes the threads for each producer and consumer
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_create(&p[i], NULL, runProducer, (void *) t);	
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_create(&c[i], NULL, runConsumer, (void *) t);

	//altougt this program doesn't end, here is the ending of it (waiting for threads to finish, etc)
	//wait the threads to finish
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_join(p[i], &status);
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_join(c[i], &status);

	pthread_join(checker, &status);

	return 0;
}