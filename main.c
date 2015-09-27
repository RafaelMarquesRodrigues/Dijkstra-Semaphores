#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_BUFFER 10
#define MAX_CONSUMERS 1
#define MAX_PRODUCERS 1
#define TRUE 1
#define FALSE 0

typedef int Semaphore;

Semaphore empty = MAX_BUFFER;
Semaphore full = 0;
Semaphore s = 1;

pthread_cond_t emptyCond;

pthread_mutex_t mutexBuffer;
pthread_cond_t fullCond;

pthread_mutex_t mutex;
pthread_cond_t consumerCond;
pthread_cond_t producerCond;

int buffer = 0;
int bufferInUse = 0;

void down(Semaphore *s, pthread_cond_t *cond, pthread_mutex_t *m, char *str){
    pthread_mutex_lock(m);

    if(*s <= 0){
        while(*s == 0)
            pthread_cond_wait(cond, m);
    }
	(*s)--;
}

void up(Semaphore *s, pthread_cond_t *cond, pthread_mutex_t *m, char *str){
    (*s)++;
    pthread_mutex_unlock(m);
	pthread_cond_signal(cond);
}


void removeProduct(){
	buffer--;
}

void *runConsumer(){
	while(TRUE){
        down(&full, &fullCond, &mutexBuffer, "consumer");
        down(&s, &consumerCond, &mutex, "consumer");
        removeProduct();
        up(&s, &producerCond, &mutex, "consumer");
        up(&empty, &emptyCond, &mutexBuffer, "consumer");
    }

	pthread_exit(NULL);
}

void createProduct(){
	buffer++;
}

void *runProducer(){
	while(TRUE){
        down(&empty, &emptyCond, &mutexBuffer, "producer");
        down(&s, &producerCond, &mutex, "producer");
        createProduct();
        up(&s, &consumerCond, &mutex, "producer");
        up(&full, &fullCond, &mutexBuffer, "producer");
    }

	pthread_exit(NULL);
}

//function to check if there is, in a given moment, more than 1 thread in the same critical region
void *runCheck(){
	while(TRUE){
        printf("%d\n", buffer);
		if(bufferInUse > 1)
			printf("Critical region problem\n");
	}
}

int main(int argc, char *argv[]){
	pthread_t producers[MAX_PRODUCERS];
	pthread_t consumers[MAX_CONSUMERS];
	pthread_t checker;
	long t = 0;
	void *status;
	int i;

	//initializes the mutex
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutexBuffer, NULL);
	
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_cond_init((void *) &(consumers[i]), NULL);
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_cond_init((void *) &producers[i], NULL);

	//initializes the funcion to check for critical access problem
	pthread_create(&checker, NULL, runCheck, (void *) t);

	//creates and initializes the threads for each producer and consumer
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_create(&producers[i], NULL, runProducer, (void *) t);	
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_create(&consumers[i], NULL, runConsumer, (void *) t);

	//altougt this program doesn't end, here is the ending of it (waiting for threads to finish, etc)
	//wait the threads to finish
	for(i = 0; i < MAX_PRODUCERS; i++)
		pthread_join(producers[i], &status);
	for(i = 0; i < MAX_CONSUMERS; i++)
		pthread_join(consumers[i], &status);

	pthread_join(checker, &status);

	return 0;
}
