#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define BUFFER_SIZE 500
int inv = 0;
pthread_mutex_t mute;
pthread_cond_t conc, conp;

void *producer(void *ptr){
	int item = 1;
	
	while(item <= BUFFER_SIZE){
		pthread_mutex_lock(&mute);
		while(inv != 0) {
			pthread_cond_wait(&conp, &mute);
			printf("producer %d has gone to sleep.\n", (int) pthread_self());
		}
		inv = item;
		pthread_cond_signal(&conc);
		pthread_mutex_unlock(&mute);
		
		printf("producer %d has created 1 item.\n", (int) pthread_self());
		
		item++;
	}
	pthread_exit(0);
}

void *consumer(void *ptr){
	int item = 1;
	
	while(item <=  BUFFER_SIZE){
		pthread_mutex_lock(&mute);
		while(inv==0) {
			pthread_cond_wait(&conc, &mute);
			printf("consumer %d has gone to sleep.\n", (int) pthread_self());
		}
		inv = 0;
		pthread_cond_signal(&conp);
		pthread_mutex_unlock(&mute);
		
		printf("consumer %d has taken 1 item.\n", (int) pthread_self());
		
		item++;
	}
	pthread_exit(0);
}

int main(int argc, char **argv)
{
	pthread_t pro[NUM_PRODUCERS], con[NUM_CONSUMERS];							//Initializing the threads
	pthread_mutex_init(&mute, 0);				//initializing the mutex to 0
	pthread_cond_init(&conc, 0);				//initializing condition of conc to 0
	pthread_cond_init(&conp, 0);				//initializing condition of conp to 0
	for (i = 0; i<NUM_CONSUMERS; i++){
	pthread_create(&con[i], 0, consumer, 0);}	//starting up consumer threads
	for (i = 0; i<NUM_PRODUCERS; i++){
	pthread_create(&pro[i], 0, producer, 0);}	//starting up producer threads
	for (i = 0; i<NUM_PRODUCERS; i++){
	pthread_join(pro[i], 0);}					//waiting for producer to end
	for (i = 0; i<NUM_CONSUMERS; i++){
	pthread_join(con[i], 0);}					//waiting for consumer to end
	pthread_cond_destroy(&conc);				//destroying condition variable conc
	pthread_cond_destroy(&conp);				//destroying condition variable conp
	pthread_mutex_destroy(&mute);				//destroying mutex mute
	
	return 0;
}