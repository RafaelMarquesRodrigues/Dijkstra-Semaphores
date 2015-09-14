#ifndef _resources_H_
#define _resources_H_

#include <pthread.h>

#define MAX_BUFFER 6
#define MAX_CONSUMERS 10
#define MAX_PRODUCERS 10
#define TRUE 1
#define FALSE 0

int empty;
int full;
int buffer;
int bufferInUse;

int pQueueSize;
int cQueueSize;
pthread_mutex_t mutex;
pthread_cond_t pQueue[MAX_PRODUCERS];
pthread_cond_t cQueue[MAX_CONSUMERS];

#endif