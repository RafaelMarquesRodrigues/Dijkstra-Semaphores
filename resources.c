#include "resources.h"
#include <stdio.h>

int full = 0;
int empty = MAX_BUFFER;
int buffer[MAX_BUFFER];

void down(char *who){
	pthread_mutex_lock(&mutex);
	printf("mutex is locked on %s...\n", who);
}

void up(char *who){
	pthread_mutex_unlock(&mutex);	
	printf("unlocking mutex on %s...\n", who);
}