#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_PRODUCERS 4							//set the number of producers
#define NUM_CONSUMERS 4							//set the number of consumers
#define BUFFER_SIZE 8							//set the max number of products
#define TO_MAKE 64								//set the number of items to make
int inv = 0;									//current number of inventory
pthread_mutex_t mute;							//mutex global variable
pthread_cond_t conc, conp;						//conditions for producer and consumer

void *producer(void *ptr){
	int item = 1;
	
	while(item <= TO_MAKE){							//creates a set number of items
		pthread_mutex_lock(&mute);						//sets the mutex
		while(inv == BUFFER_SIZE) {								//puts thread to sleep if inv is full
			printf("producer %d has found the inventory full and is waiting for consumers.\n", (int) pthread_self());
			pthread_cond_wait(&conp, &mute);
		}
		inv += 1;									//incrementing the inventory
		pthread_cond_signal(&conc);						//sets the condition for consumer
		pthread_mutex_unlock(&mute);					//unlocks the mutex
		
		printf("producer %d has created 1 item.\n", (int) pthread_self());
		
		item++;
	}
	pthread_exit(0);
}

void *consumer(void *ptr){
	int item = 1;
	
	while(item <=  TO_MAKE){						//consumes a set number of items
		pthread_mutex_lock(&mute);						//sets the mutex
		while(inv==0) {									//puts thread to sleep if inv is empty
			printf("consumer %d has found the inventory empty and is waiting for it to be filled.\n", (int) pthread_self());
			pthread_cond_wait(&conc, &mute);
		}
		inv -= 1;										//decrementing the inventory
		pthread_cond_signal(&conp);						//sets the conditino for the producer
		pthread_mutex_unlock(&mute);					//unlocks the mutex
		
		printf("consumer %d has taken 1 item.\n", (int) pthread_self());
		
		item++;
	}
	pthread_exit(0);
}

int main(int argc, char **argv)
{
	int i;
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
	
	printf("The ending inventory is: %d\n", inv);
	return 0;
}