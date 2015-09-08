#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "resources.h"
#include "consumer.h"
#include "producer.h"

int main(int argc, char *argv[]){
	pthread_t p[MAX_THREADS];
	long t = 0;
	void *status;

	//initizalizes the mutex
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condProducer, NULL);
	pthread_cond_init(&condConsumer, NULL);
	
	//creates and initialie the threads
	pthread_create(&p[0], NULL, runConsumer, (void *) t);
	pthread_create(&p[1], NULL, runProducer, (void *) t);	

	//wait the thread finish
	pthread_join(p[0], &status);
	pthread_join(p[1], &status);

	//destroy resources
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condConsumer);
	pthread_cond_destroy(&condProducer);

	return 0;
}