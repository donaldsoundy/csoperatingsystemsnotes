#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILDREN 2

int main(int argc, char *argv[])
{
	printf("I am parent: %d\n", (int) getpid());
	int parent = (int) getpid();
	
	while(i<NUM_CHILDREN){
		if((int) getpid() == parent){
		fork();
		}
	}
	
	if((int) getpid() != parent){
		printf("Hello, PID: %d\n", (int) getpid());
	}
	return 0;
}
