#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM_CHILDREN 8

int main(int argc, char *argv[])
{
	pid_t parentPid, childPid;
	int s= 0;
	
	printf("I am parent: %d\n", (int) getpid());
	int parent = (int) getpid();
	
	int i = 0;
	
	while(i<NUM_CHILDREN){
		if ((childPid = fork()) < 0) {
			printf("ERROR creating child. returned<0");
			exit(0);
		}
		if ((int) getpid() != parent) {
			printf("Hello, PID: %d\n", (int) getpid());
			exit(0);
		}
		i++;
	}
	while((parentPid = wait(&s)) > 0);
	return 0;
}
