#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <pthread.h>

#define MAX_BUFFER 5
#define MAX_THREADS 2
#define TRUE 1
#define FALSE 0

pthread_cond_t condProducer;
pthread_cond_t condConsumer;
pthread_mutex_t mutex;
int full;
int empty;
int buffer[MAX_BUFFER];

void down(char *);
void up(char *);

#endif